# include <bits/stdc++.h>
using namespace std;

void perm(string, int);
int cnt{0};

int main(void){
    string sor = "";
    cin>>sor;
    sort(sor.begin(), sor.end());
    perm(sor, 0);
    cout<<"Total："<<cnt<<endl;
    return 0;
}

void perm(string sor, int index){
    if(index == sor.size()-1){                      //終止條件，找到最後表此輪結束
        for(int i = 0; i<sor.size(); i++){
            cout<<sor[i];
        }
        cout<<endl;
        cnt++;
    }
    else{
        for(int i = index; i<sor.size(); i++){
            bool boom = false;                      //判斷使否排過
            for(int j = index; j<i; j++){           //前面是排過的，如果前面有與我相同的字，代表已經找過
                if(sor[i] == sor[j]){
                    boom = true;
                    break;                          //已經確認排過
                }
            }
            if(boom) continue;                      //不浪費資源做重複的事
            swap(sor[i], sor[index]);               //交換以嘗試各種不同的排列組合
            perm(sor, index+1);                     //進入判斷
            swap(sor[i], sor[index]);               //將換過的結果恢復，以讓i指到下一個繼續遞迴
        }
    }
}
