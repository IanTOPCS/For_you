# include <bits/stdc++.h>
using namespace std;

bool par(string, int, int);

int main(void){
    string sor = "";
    cin>>sor;
    int mid = ceil(sor.size()/2);               //眏砏﹚
    cout<<par(sor, mid, 0)<<endl;
    return 0;
}

bool par(string sor, int mid, int index){
    if(index == mid) return 1;                  //狦い丁⊿癶癹伴碞琌玡常才砏玥
    if(sor[index] == sor[sor.size()-1-index]){  //狦才ゅ砏玥碞膥尿患癹
        return par(sor, mid, index+1);
    }
    return 0;                                   //ぃ才碞癶
}
