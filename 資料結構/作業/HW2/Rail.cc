# include <bits/stdc++.h>
using namespace std;

void perm(int**, int*, int, int);
int fab(int);
bool judge_stack(int*, int);

int impossible_line{0};                                     // 紀錄不可能產生的排列（維護真實個數）

int main(void){                                             // O(n^3)
    int num{0}; cin>>num;

    int **impossible_table = new int*[fab(num)];            // 不可能產生的排列，不知道有幾個 但不可能超過所有可能（此題答案）
    for(int i = 0; i<fab(num); i++){
        impossible_table[i] = new int[num];
    }

    int *sor = new int[num];                                // 位於Rail的數字（為了產生窮舉排列，順序沒差）
    for(int i = 0; i<num; i++) sor[i] = i;

    perm(impossible_table, sor, 0, num);                    // 獲得所有排列

    cout<<"Ans:"<<impossible_line<<endl;
    for(int i = 0; i<impossible_line; i++){                 // 印出所求
        for(int j = 0; j<num; j++){
            cout<<impossible_table[i][j]<<" ";
        }
        cout<<endl;
    }
    

    // ofstream file;                                       // 寫檔案
    // file.open("./output.txt");
    // file<<"輸出列數: 不可能排列答案"<<endl;
    // for(int i = 0; i<impossible_line; i++){              // 寫出output.txt 至此層資料夾，輸入6以上會終端機會不完整（10 為極限，及 output.txt內容，11輸入記憶體爆炸）
    //     file<<left<<setw(8)<<i+1<<": ";                  // 39916800為總排列數，其中數字會因為 可能or不可能 而降低，但記憶體最多要到約 1000*1000*4 bytes，39916800*11*4 bytes很明顯超出
    //     for(int j = 0; j<num; j++){
    //         file<<impossible_table[i][j]<<" ";
    //     }
    //     file<<endl;
    // }
    // file.close();

    for(int i = 0; i<fab(num); i++){                        // avoid memory leak
        delete[] impossible_table[i];
    }
    delete[] impossible_table;
    delete[] sor;

    return 0;
}

void perm(int **impossible_table, int *sor, int index, int size){                  // 暴力窮舉 O(n^2)
    if(index == size-1){                                                           // 得出一組排列
        bool flag = judge_stack(sor, size);                                        // 模擬真實 stack O(n)
        if(flag == false){                                                         // 不可能產生，存入答案
            for(int j = 0; j<size; j++){
                impossible_table[impossible_line][j] = sor[j];
            }
            impossible_line++;
        }
    }
    for(int i = index; i<size; i++){
        swap(sor[index], sor[i]);
        perm(impossible_table, sor, index+1, size);
        swap(sor[index], sor[i]);
    }
}

int fab(int num){                                                                   // 一開始要動態多少陣列的來源
    int ans{1};
    for(int i = 1; i<=num; i++){
        ans *= i;
    }
    return ans;
}

bool judge_stack(int *suppose_stack, int size){                                     // 檢查 假設成立的stack 是否真的成立
    bool flag{false};
    int *real_stack = new int[size];
    int suppose_now{0}, real_now{0}, put_in{0};
    while((put_in < size) && (suppose_now < size)){
        real_stack[real_now] = put_in;                                              // 按照題意放入真實stack
        while(real_stack[real_now] == suppose_stack[suppose_now]){                  // 在真實 stack 裡有與假設答案的 stack 相同
            real_now--;                                                             // 真實stack拿出最上層
            suppose_now++;                                                          // 在此刻與假設成立，比較下一刻的假設
            if(real_now == -1) break;                                               // 在目前，真實stack已經沒東西了（可能來源鐵軌還有資料，現在沒得比了）
        }
        if(suppose_now == size){                                                    // 全部假設皆成立，為可能的排列
            flag = true;
        }
        put_in++, real_now++;                                                       // 不管有沒有與假設相同，都要放入（如果沒有，放入是為了看下一個可不可能與當前假設相同）/(如果有，也早拿出真實堆疊了，可能處於沒有任何值，必須增加真實堆疊)
    }
    delete[] real_stack;
    return flag;
}
