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

using namespace std;

string trim(const string& str) {
    auto start = find_if_not(str.begin(), str.end(), [](unsigned char c) { return isspace(c); });
    auto end = find_if_not(str.rbegin(), str.rend(), [](unsigned char c) { return isspace(c); }).base();
    return (start >= end) ? "" : string(start, end);
}

void sigint_handler(int sig) {
    cout << "\nCaught SIGINT (Ctrl+C)\n";
    fflush(stdout);
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

vector<char*> to_cstrs(const vector<string>& args) {
    vector<char*> result;
    for (const auto& arg : args)
        result.push_back(const_cast<char*>(arg.c_str()));
    result.push_back(nullptr);
    return result;
}

void execute_command(vector<string> args, bool background = false,
                     const string& inFile = "", const string& outFile = "", bool append = false) {
    if (args.empty()) {
        cerr << "No command provided" << endl;
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // 子進程
        if (!inFile.empty()) {
            int fd = open(inFile.c_str(), O_RDONLY);
            if (fd < 0) { perror(("open inFile: " + inFile).c_str()); exit(1); }
            if (dup2(fd, STDIN_FILENO) < 0) { perror("dup2 inFile"); exit(1); }
            close(fd);
        }

        if (!outFile.empty()) {
            int fd = open(outFile.c_str(),
                          append ? (O_WRONLY | O_CREAT | O_APPEND) : (O_WRONLY | O_CREAT | O_TRUNC),
                          0644);
            if (fd < 0) { perror(("open outFile: " + outFile).c_str()); exit(1); }
            if (dup2(fd, STDOUT_FILENO) < 0) { perror("dup2 outFile"); exit(1); }
            close(fd);
        }

        vector<char*> cargs = to_cstrs(args);
        execvp(cargs[0], cargs.data());
        perror(("execvp: " + args[0]).c_str());
        exit(1);
    } else if (pid > 0) {
        // 父進程
        if (!background) {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                cerr << "Command '" << args[0] << "' failed with exit code " << WEXITSTATUS(status) << endl;
            }
        }
    } else {
        perror("fork");
    }
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

void execute_pipeline(const vector<string>& pipelineParts,
                      const string& inFile = "",
                      const string& outFile = "",
                      bool append = false) {
    int input = 0;  // 初始為 stdin
    int fd[2];

    for (size_t i = 0; i < pipelineParts.size(); ++i) {
        if (i < pipelineParts.size() - 1) {
            if (pipe(fd) < 0) {
                perror("pipe");
                return;
            }
        }

        pid_t pid = fork();
        if (pid == 0) {
            // 子進程

            // Step 1: Input 重定向（僅限第一個）
            if (i == 0 && !inFile.empty()) {
                int infd = open(inFile.c_str(), O_RDONLY);
                if (infd < 0) {
                    perror(("open input file: " + inFile).c_str());
                    exit(1);
                }
                if (dup2(infd, STDIN_FILENO) < 0) {
                    perror("dup2 input file");
                    exit(1);
                }
                close(infd);
            } else if (input != 0) {
                if (dup2(input, STDIN_FILENO) < 0) {
                    perror("dup2 previous input");
                    exit(1);
                }
                close(input);
            }

            // Step 2: Output 重定向（僅限最後一個）
            if (i == pipelineParts.size() - 1 && !outFile.empty()) {
                int outfd = open(outFile.c_str(),
                                 append ? (O_WRONLY | O_CREAT | O_APPEND) : (O_WRONLY | O_CREAT | O_TRUNC),
                                 0644);
                if (outfd < 0) {
                    perror(("open output file: " + outFile).c_str());
                    exit(1);
                }
                if (dup2(outfd, STDOUT_FILENO) < 0) {
                    perror("dup2 output file");
                    exit(1);
                }
                close(outfd);
            } else if (i < pipelineParts.size() - 1) {
                if (dup2(fd[1], STDOUT_FILENO) < 0) {
                    perror("dup2 pipe write");
                    exit(1);
                }
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
            perror(("execvp: " + tokens[0]).c_str());
            exit(1);
        } else if (pid > 0) {
            // 父進程
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                cerr << "Pipeline command failed with exit code " << WEXITSTATUS(status) << endl;
            }

            // 關閉不再使用的 pipe
            if (input != 0) close(input);
            if (i < pipelineParts.size() - 1) {
                close(fd[1]);
                input = fd[0];
            }
        } else {
            perror("fork");
            return;
        }
    }
}

int main() {
    signal(SIGINT, sigint_handler);

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        line = trim(line);
        if (line.empty()) continue;
        if (line == "exit") break;

        // Handle conditional execution
        vector<string> condParts = split(line, '&');
        if (condParts.size() == 2 && condParts[1][0] == '&') {
            condParts[1] = trim(condParts[1].substr(1));
            vector<string> first_cmd = split(condParts[0], ' ');
            if (first_cmd.empty()) continue;

            int status = 0;
            pid_t pid = fork();
            if (pid == 0) {
                vector<char*> cargs = to_cstrs(first_cmd);
                execvp(cargs[0], cargs.data());
                perror(("execvp: " + first_cmd[0]).c_str());
                exit(1);
            } else if (pid > 0) {
                waitpid(pid, &status, 0);
                if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                    vector<string> second_cmd = split(condParts[1], ' ');
                    if (!second_cmd.empty()) {
                        execute_command(second_cmd);
                    }
                }
            } else {
                perror("fork");
            }
            continue;
        }

        // Handle pipelines
        if (line.find('|') != string::npos) {
            vector<string> pipeParts = split(line, '|');
            if (pipeParts.empty()) continue;
            execute_pipeline(pipeParts);
            continue;
        }

        // Handle redirection
        string inFile, outFile;
        bool append = false;
        bool background = false;

        // 處理輸入重定向 '<'
        size_t inPos = line.find('<');
        if (inPos != string::npos) {
            size_t start = inPos + 1;
            while (start < line.size() && isspace(line[start])) ++start;
            size_t end = start;
            while (end < line.size() && !isspace(line[end]) && line[end] != '>' && line[end] != '<') ++end;
            inFile = trim(line.substr(start, end - start));
            line.erase(inPos, end - inPos);
            line = trim(line);
        }

        // 處理輸出重定向 '>>' 或 '>'
        size_t outPos = line.find(">>");
        if (outPos != string::npos) {
            size_t start = outPos + 2;
            while (start < line.size() && isspace(line[start])) ++start;
            size_t end = start;
            while (end < line.size() && !isspace(line[end])) ++end;
            outFile = trim(line.substr(start, end - start));
            append = true;
            int fd = open(outFile.c_str(), O_WRONLY | O_CREAT, 0644);
            if (fd < 0) { perror(("Cannot create output file: " + outFile).c_str()); }
            else { close(fd); }
            line.erase(outPos, end - outPos);
        } else if ((outPos = line.find('>')) != string::npos) {
            size_t start = outPos + 1;
            while (start < line.size() && isspace(line[start])) ++start;
            size_t end = start;
            while (end < line.size() && !isspace(line[end])) ++end;
            outFile = trim(line.substr(start, end - start));
            append = false;
            int fd = open(outFile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) { perror(("Cannot create output file: " + outFile).c_str()); }
            else { close(fd); }
            line.erase(outPos, end - outPos);
        }

        vector<string> tokens = split(line, ' ');
        if (!tokens.empty()) {
            execute_command(tokens, background, inFile, outFile, append);
        }
    }

    return 0;
}