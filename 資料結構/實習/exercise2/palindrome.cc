# include <bits/stdc++.h>
using namespace std;

bool par(string, int, int);

int main(void){
    string sor = "";
    cin>>sor;
    int mid = ceil(sor.size()/2);               // 無條件捨去，目的為找到那裡停下
    cout<<par(sor, mid, 0)<<endl;
    return 0;
}

bool par(string sor, int mid, int index){
    if(index == mid) return 1;                  // 回文判定，如果到中間（回文判斷終點）都相同，就是回文
    if(sor[index] == sor[sor.size()-1-index]){  // 如果目前跟相對位置相同，繼續檢查下一順位
        return par(sor, mid, index+1);
    }
    return 0;                                   // 目前與相對位置不同，非回文
}
