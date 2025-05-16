#include <sstream>
#include <signal.h>
#include <algorithm>
#include <cctype>
#include <locale>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <sys/wait.h>
#include <errno.h>
#include <pwd.h>

using namespace std;

pid_t current_child_pid = -1;

string trim(const string& str) {
    auto start = find_if_not(str.begin(), str.end(), [](unsigned char c) { return isspace(c); });
    auto end = find_if_not(str.rbegin(), str.rend(), [](unsigned char c) { return isspace(c); }).base();
    return (start >= end) ? "" : string(start, end);
}

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        token = trim(token);
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

struct ParsedCommand {
    vector<string> pipelineParts;
    string inFile;
    string outFile;
    bool append = false;
};

ParsedCommand parse_pipeline_with_redirection(const string& line) {
    ParsedCommand result;
    string cmd = line;

    // 處理輸入重定向
    size_t inPos = cmd.find('<');
    if (inPos != string::npos) {
        size_t end = cmd.find_first_of("><|", inPos + 1); // 假設檔名之後為其他符號或結尾
        result.inFile = trim(cmd.substr(inPos + 1, end - inPos - 1));
        cmd.erase(inPos, (end == string::npos ? cmd.size() : end) - inPos);
    }

    // 處理輸出重定向（先處理 >> 再處理 >）
    size_t outPos = cmd.find(">>");
    if (outPos != string::npos) {
        result.append = true;
        size_t end = cmd.find_first_of("<|", outPos + 2);
        result.outFile = trim(cmd.substr(outPos + 2, end - outPos - 2));
        cmd.erase(outPos, (end == string::npos ? cmd.size() : end) - outPos);
    } else {
        outPos = cmd.find('>');
        if (outPos != string::npos) {
            size_t end = cmd.find_first_of("<|", outPos + 1);
            result.outFile = trim(cmd.substr(outPos + 1, end - outPos - 1));
            cmd.erase(outPos, (end == string::npos ? cmd.size() : end) - outPos);
        }
    }

    // 拆分 pipeline
    result.pipelineParts = split(cmd, '|');
    return result;
}


vector<char*> to_cstrs(const vector<string>& args) {
    vector<char*> result;
    for (const auto& arg : args)
        result.push_back(const_cast<char*>(arg.c_str()));
    result.push_back(nullptr);
    return result;
}

vector<string> split_command_with_quotes(const string& line) {
    vector<string> tokens;
    string token;
    bool inQuotes = false;

    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];

        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (isspace(c) && !inQuotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    return tokens;
}

bool execute_pipeline(const vector<string>& pipelineParts,
                      const string& inFile = "",
                      const string& outFile = "",
                      bool append = false) {
    int input = 0;  // 初始為 stdin
    int fd[2];
    bool meetError{false};
    for (size_t i = 0; i < pipelineParts.size(); ++i) {
        if (i < pipelineParts.size() - 1) {
            if (pipe(fd) < 0) {
                perror("pipe");
                return true;
            }
        }

        pid_t pid = fork();
        if (pid == 0) {
            // 子進程
            signal(SIGINT, SIG_DFL);  // 恢復預設中斷行為

            // Input 重定向
            if (i == 0 && !inFile.empty()) {
                int infd = open(inFile.c_str(), O_RDONLY);
                if (infd < 0) {
                    perror(("open input file: " + inFile).c_str());
                    exit(1);
                }
                dup2(infd, STDIN_FILENO);
                close(infd);
            } else if (input != 0) {
                dup2(input, STDIN_FILENO);
                close(input);
            }

            // Output 重定向
            if (i == pipelineParts.size() - 1 && !outFile.empty()) {
                int outfd = open(outFile.c_str(),
                                 append ? (O_WRONLY | O_CREAT | O_APPEND) : (O_WRONLY | O_CREAT | O_TRUNC),
                                 0644);
                if (outfd < 0) {
                    perror(("open output file: " + outFile).c_str());
                    exit(1);
                }
                dup2(outfd, STDOUT_FILENO);
                close(outfd);
            } else if (i < pipelineParts.size() - 1) {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
            }

            // 執行該指令
            vector<string> tokens = split_command_with_quotes(pipelineParts[i]);
            if (tokens.empty()) {
                cerr << "Empty command in pipeline" << endl;
                exit(1);
            }
            vector<char*> cargs = to_cstrs(tokens);
            execvp(cargs[0], cargs.data());
            perror(("myShell: " + tokens[1]).c_str());
            exit(1);
        } else if (pid > 0) {
            // 父進程
            current_child_pid = pid;

            int status;
            waitpid(pid, &status, 0);

            current_child_pid = -1;  // 清除追蹤

            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                // cerr << "Pipeline command failed with exit code " << WEXITSTATUS(status) << endl;
                return true;
            }

            // 關閉不再使用的 pipe
            if (input != 0) close(input);
            if (i < pipelineParts.size() - 1) {
                close(fd[1]);
                input = fd[0];
            }
        } else {
            perror("fork");
            return true;
        }
    }
    return false;
}


vector<string> split_by_double_ampersand(const string& line) {
    vector<string> result;
    string token;
    bool in_single_quote = false, in_double_quote = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (c == '"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
            token += c;
        } else if (c == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
            token += c;
        } else if (!in_single_quote && !in_double_quote && c == '&' && i + 1 < line.size() && line[i + 1] == '&') {
            result.push_back(trim(token));
            token.clear();
            ++i; // skip second '&'
        } else {
            token += c;
        }
    }

    if (!token.empty()) {
        result.push_back(trim(token));
    }

    return result;
}

string get_prompt_path(bool meetFalse) {
    size_t size = 128;
    vector<char> buffer(size);

    // 嘗試使用 getcwd，如果緩衝區不夠就擴充
    while (getcwd(buffer.data(), buffer.size()) == nullptr) {
        if (errno != ERANGE) {
            perror("getcwd");
            return "$ ";
        }
        size *= 2;
        buffer.resize(size);
    }

    string currentDir(buffer.data());

    const char* home = getenv("HOME");
    if (!home) {
        struct passwd* pw = getpwuid(getuid());
        if (pw) home = pw->pw_dir;
    }

    if (home && currentDir.find(home) == 0) {
        currentDir.replace(0, strlen(home), "~");
    }

    // 取得使用者名稱
    struct passwd* pw = getpwuid(getuid());
    string username = pw ? pw->pw_name : "user";

    // ANSI 顏色
    string cyan = "\x1b[32m";   // 使用者顏色
    string red = "\x1b[31m";    // 箭頭(錯誤)顏色
    string blue = "\x1b[1;94m";   // 目錄顏色
    string reset = "\x1b[0m";   // 重置顏色

    string arrowColor = "\x1b[37m";
    if (meetFalse == true) arrowColor = red;

    return cyan + username + reset + arrowColor + " ➜ " + reset + blue + currentDir + reset + " $ ";
}


void sigint_handler(int sig) {
    if (current_child_pid > 0) {
        kill(current_child_pid, SIGINT); // 傳送 Ctrl+C 到子行程
    } else {
        cout << "\n"; // 換行
        cout<< get_prompt_path(true);
        cout.flush();
    }
}

string getInputLine(string line){
    string ansLine{""};
    while(true){
        string tmpLine{""};
        getline(cin, tmpLine);
        if(tmpLine[tmpLine.size()-1] == '\\'){
            ansLine += tmpLine;
            cout<<"> ";
            continue;
        }
        ansLine += tmpLine;
        break;
    }
    ansLine.erase(std::remove(ansLine.begin(), ansLine.end(), '\\'), ansLine.end());
    return ansLine;
}

int main() {
    signal(SIGINT, sigint_handler);
    bool displayFalse = false;
    string line{""};
    while (true) {
        cout << get_prompt_path(displayFalse);
        line = trim(getInputLine(line));
        if (line.empty()) continue;
        if (line == "exit") break;

        // Handle conditional execution with multiple &&
        if (line.find("&&") != string::npos) {
            vector<string> parts = split_by_double_ampersand(line);
            bool success = true;

            for (const string& part : parts) {
                if (!success) break;

                ParsedCommand parsed = parse_pipeline_with_redirection(part);
                if (parsed.pipelineParts.empty()) continue;

                int status = 0;
                pid_t pid = fork();
                if (pid == 0) {
                    // 子進程執行整個 pipeline（含 redirection）
                    bool meetFalse = execute_pipeline(parsed.pipelineParts, parsed.inFile, parsed.outFile, parsed.append);
                    if (meetFalse == true){
                        displayFalse = true;
                        success = false;
                    }
                } else if (pid > 0) {
                    waitpid(pid, &status, 0);
                    if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0)) {
                        success = false; // 如果當前失敗，就停止執行後續
                        displayFalse = true;
                    }
                } else {
                    perror("fork");
                    break;
                }
            }
            if (displayFalse == true) continue;
            else{
                displayFalse = false;
                continue;
            }
        }

        ParsedCommand parsed = parse_pipeline_with_redirection(line);
        if (!parsed.pipelineParts.empty()) {
            displayFalse = execute_pipeline(parsed.pipelineParts, parsed.inFile, parsed.outFile, parsed.append);
        }
        if (displayFalse == true) continue;
        else{
            displayFalse = false;
            continue;
        }
    }

    return 0;
}