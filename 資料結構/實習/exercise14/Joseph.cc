#include <bits/stdc++.h>
using namespace std;

// 函數用來找到給定 k 的最小 m
int find_min_m(int k) {
    int m = 1;                                                      // 從 m = 1 開始測試
    while (true) {
        int *people = new int[2 * k];                               // k 好人 k 壞人
        for (int i = 0; i < 2 * k; ++i) {                           // 初始編號
            people[i] = i + 1;
        }

        int size = 2 * k;                                           // 當前圈中剩餘人數
        int index = 0;                                              // 起始位置
        bool valid = true;                                          // 是否為正確答案(砍到好人即false，失敗)

        for (int count = 0; count < k; ++count) {                   // 確保壞人全部被處決
            index = (index + m - 1) % size;                         // 計算要處決的索引
            if (people[index] <= k) {                               // 如果處決到好人(失敗，判斷下一輪)
                valid = false;
                break;
            }

            for (int j = index; j < size - 1; ++j) {                // 將人移除，陣列縮小（將此空位用後面的覆蓋）
                people[j] = people[j + 1];
            }
            size--;                                                 // 縮小圈的大小（丟掉最後一格）
        }

        if (valid) {
            delete[] people;
            return m;                                               // 如果全部壞人都被先處決(正確結果)，回傳 m
        }
        m++;                                                        // 測試下一個 m
    }
}

int main(void) {
    int k{0};
    while (cin >> k && k != 0) {                                    // 讀取輸入直到 k = 0
        cout<<find_min_m(k)<<endl;
    }
    return 0;
}
