# include <bits/stdc++.h>
using namespace std;

void optimalBST(const vector<double>& p, const vector<double>& q, int n) {
    vector<vector<double>> e(n+2, vector<double>(n+1));  // 期望成本 e[i][j]
    vector<vector<double>> w(n+2, vector<double>(n+1));  // 機率總和 w[i][j]
    vector<vector<int>> root(n+1, vector<int>(n+1));     // 根節點位置 root[i][j]

    // 初始化：e[i][i-1] 與 w[i][i-1]
    for (int i = 1; i <= n+1; i++) {
        e[i][i-1] = q[i-1];
        w[i][i-1] = q[i-1];
    }

    // 動態規劃主體
    for (int l = 1; l <= n; l++) {  // l 是子樹長度
        for (int i = 1; i <= n - l + 1; i++) {  // i 是子樹的起始位置, i + l - 1 是子樹的結束位置n
            int j = i + l - 1;                  // j 是子樹的結束位置
            e[i][j] = numeric_limits<double>::infinity();
            w[i][j] = w[i][j-1] + p[j-1] + q[j];    // 上一個機率總和 + 當前找到機率 + 當前未找到機率
            for (int r = i; r <= j; r++) {
                double t = e[i][r-1] + e[r+1][j] + w[i][j]; // 左子樹 + 右子樹 + 機率總和(深度+1，子樹機率再加一次，如原本須被訪問3次，3*p => (3+1)*p)
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << "Minimum expected cost: " << e[1][n] << endl;
    cout << "Root table:" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            cout << root[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<double> p = {0.15, 0.05, 0.10, 0.10, 0.20};  // 搜尋鍵的機率 pi
    vector<double> q = {0.10, 0.05, 0.05, 0.05, 0.05, 0.10};  // 假鍵的機率 qi
    int n = p.size();
    optimalBST(p, q, n);
    return 0;
}