// 這是碩班高等Unix課程作業，目標是打印出目標資料夾內的所有資料，以樹狀結構展開，可指定參數(終端機指令)
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <limits.h>

using namespace std;

bool humanReadable = false;
bool showPermissions = false;
bool sortAlpha = false;
bool sortReverse = false;

#define RESET       "\033[0m"
#define COLOR_DIR   "\033[1;34m"
#define COLOR_EXEC  "\033[1;32m"
#define COLOR_LINK  "\033[1;36m"
#define COLOR_FIFO  "\033[0;33m"
#define COLOR_CHAR  "\033[1;33m"
#define COLOR_BLOCK "\033[1;35m"
#define COLOR_REG   "\033[0m"

string formatSize(off_t size) {
    const char* units[] = {"B", "K", "M", "G", "T"};
    int i = 0;
    double dsize = size;
    while (dsize >= 1024 && i < 4) {
        dsize /= 1024.0;
        ++i;
    }
    stringstream ss;
    if (dsize == (int)dsize) {
        ss << (int)dsize << " " << units[i];
    } else {
        ss << fixed << setprecision(2) << dsize << " " << units[i];
    }
    return ss.str();
}

string getPermissions(mode_t mode) {
    string p;
    p += (S_ISDIR(mode)) ? "d" :
         (S_ISLNK(mode)) ? "l" :
         (S_ISCHR(mode)) ? "c" :
         (S_ISBLK(mode)) ? "b" :
         (S_ISFIFO(mode)) ? "p" : "-";

    p += (mode & S_IRUSR) ? "r" : "-";
    p += (mode & S_IWUSR) ? "w" : "-";
    p += (mode & S_IXUSR) ? "x" : "-";
    p += (mode & S_IRGRP) ? "r" : "-";
    p += (mode & S_IWGRP) ? "w" : "-";
    p += (mode & S_IXGRP) ? "x" : "-";
    p += (mode & S_IROTH) ? "r" : "-";
    p += (mode & S_IWOTH) ? "w" : "-";
    p += (mode & S_IXOTH) ? "x" : "-";
    return p;
}

string getGradientColor(int depth) {
  int startColor = 33;
  int endColor = 196;
  int colorRange = endColor - startColor;
  int steps = 5;

  int colorCode = startColor + (depth % steps) * colorRange / steps;
  if (colorCode > 255) colorCode = 255;

  return "\033[38;5;" + to_string(colorCode) + "m";
}

string renderPrefix(const string& prefix) {
  string result;
  int level = 0;
  size_t i = 0;

  while (i < prefix.size()) {
      // 嘗試匹配 UTF-8 的 │（三個 byte：0xE2 0x94 0x82）
      if (prefix[i] == '\xE2' && prefix[i+1] == '\x94' && prefix[i+2] == '\x82') {
          result += getGradientColor(level++) + "│" + RESET;
          i += 3; // 跳過這三個 byte
      } else {
          result += prefix[i];
          ++i;
      }
  }

  return result;
}

string getColor(mode_t mode) {
    if (S_ISDIR(mode)) return COLOR_DIR;
    if (S_ISLNK(mode)) return COLOR_LINK;
    if (S_ISFIFO(mode)) return COLOR_FIFO;
    if (S_ISCHR(mode)) return COLOR_CHAR;
    if (S_ISBLK(mode)) return COLOR_BLOCK;
    if (mode & S_IXUSR) return COLOR_EXEC;
    return COLOR_REG;
}

int countFiles(const string& path) {
    DIR* dir = opendir(path.c_str());
    if (!dir) return 0;
    int count = 0;
    struct dirent* entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
            count++;
    }
    closedir(dir);
    return count;
}

void listTree(const string& path, const string& prefix, int depth){
    DIR* dir = opendir(path.c_str());
    if (!dir) {
        cerr << "Cannot open directory: " << path << endl;
        return;
    }

    vector<string> entries;
    struct dirent* entry;
    while ((entry = readdir(dir))) {
        string name = entry->d_name;
        if (name != "." && name != "..") {
            entries.push_back(name);
        }
    }
    closedir(dir);

    // 排序
    if (sortAlpha || sortReverse) {
        sort(entries.begin(), entries.end());
        if (sortReverse) reverse(entries.begin(), entries.end());
    }

    for (size_t i = 0; i < entries.size(); ++i) {
        string fullPath = path + "/" + entries[i];
        struct stat st;
        lstat(fullPath.c_str(), &st);

        string color = getColor(st.st_mode);
        string renderedPrefix = renderPrefix(prefix);
        string branchColor = getGradientColor(depth);
        cout << renderedPrefix << branchColor << "+-- " << RESET << color << entries[i] << RESET;

        // 顯示符號連結目標
        if (S_ISLNK(st.st_mode)) {
            char buf[PATH_MAX];
            ssize_t len = readlink(fullPath.c_str(), buf, sizeof(buf) - 1);
            if (len != -1) {
                buf[len] = '\0';
                cout << " → " << buf;
            }
        }

        // 顯示權限與大小
        if (showPermissions) {
            cout << " (" << getPermissions(st.st_mode);
            if (!S_ISDIR(st.st_mode)) {
                cout << " ";
                if (humanReadable)
                    cout << formatSize(st.st_size);
                else
                    cout << st.st_size;
            }
            cout << ")";
        } else {
            if (S_ISDIR(st.st_mode)) {
                int n = countFiles(fullPath);
                cout << " (" << n << " file" << (n != 1 ? "s" : "") << ")";
            } else {
                if (humanReadable)
                    cout << " (" << formatSize(st.st_size) << ")";
                else
                    cout << " (" << st.st_size << ")";
            }
        }

        cout << endl;

        // 遞迴處理資料夾
        if (S_ISDIR(st.st_mode)) {
          listTree(fullPath, prefix + "│   ", depth + 1);
        }
    }
}

int main(int argc, char* argv[]) {
    vector<string> directories;

    for (int i = 1; i < argc; ++i) {
      string arg = argv[i];
  
      if (!arg.empty() && arg[0] == '-') {
          for (size_t j = 1; j < arg.length(); ++j) {
              char flag = arg[j];
              switch (flag) {
                  case 'h':
                      humanReadable = true;
                      break;
                  case 'p':
                      showPermissions = true;
                      break;
                  case 'a':
                      sortAlpha = true;
                      break;
                  case 'r':
                      sortReverse = true;
                      break;
                  default:
                      cerr << "Unknown flag: -" << flag << endl;
                      break;
              }
          }
      } else {
          directories.push_back(arg);
      }
    }

    if (directories.empty()) {
        directories.push_back("./");
    }

    for (size_t i = 0; i < directories.size(); ++i) {
        cout << directories[i] << endl;
        listTree(directories[i], "", 0);
        if (i != directories.size() - 1) {
            cout << endl;
        }
    }

    return 0;
}
