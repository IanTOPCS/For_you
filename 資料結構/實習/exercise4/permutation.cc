# include <bits/stdc++.h>
using namespace std;

void perm(string, int);
int cnt{0};

int main(void){
    string sor = "";
    cin>>sor;
    sort(sor.begin(), sor.end());
    perm(sor, 0);
    cout<<"Total:"<<cnt<<endl;
    return 0;
}

void perm(string sor, int index){
    if(index == sor.size()-1){                      // 已經到最後位置，為一組排列
        for(int i = 0; i<sor.size(); i++){
            cout<<sor[i];
        }
        cout<<endl;
        cnt++;
    }
    else{
        for(int i = index; i<sor.size(); i++){      // 當此為開頭，開始一個一個看是否排列（i 之前為已經排過的）
            bool boom = false;                      // 以 flag 判斷是否重複過
            for(int j = index; j<i; j++){           // 從前面排過來的，故只要前面出現過（檢查到 i 為止）
                if(sor[i] == sor[j]){
                    boom = true;
                    break;                          // 有重複，後面可以不用判斷
                }
            }
            if(boom) continue;                      // 已經做過，關注下個順位
            swap(sor[i], sor[index]);               // 嘗試交換
            perm(sor, index+1);                     // 交換完判斷（交給下個我）
            swap(sor[i], sor[index]);               // 判斷玩交換回來
        }
    }
}
