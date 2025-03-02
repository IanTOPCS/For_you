# include <bits/stdc++.h>
using namespace std;

class Act{
public:
    int start;
    int end;
    Act(int start, int end);
};

Act::Act(int start = 0, int end = 0){
    this->start = start;
    this->end = end;
}

int ActCnt(Act *myAct = nullptr, int num = 0);

int main(void){
    int num{0}; cin>>num;
    Act *myAct = new Act[num];
    for(int i = 0; i<num; i++){
        int st{0}, ed{0}; cin>>st>>ed;
        myAct[i] = Act(st, ed);
    }
    cout<<ActCnt(myAct, num)<<"\n";
    delete[] myAct;
    return 0;
}

int ActCnt(Act *myAct, int num){
    sort(myAct, myAct+num, [](Act a, Act b){return a.end < b.end;});    // 按照結束時間排序，越早結束，越多時間參加另外活動
    int cnt{0}, lastAct{-1};                                            // 第一個活動必定參加
    for(int i = 0; i<num; i++){
        if(myAct[i].start >= lastAct){                                  // 當下個活動開始時間在我上一個活動已經結束，參加
            cnt++;
            lastAct = myAct[i].end;
        }
    }
    return cnt;
}