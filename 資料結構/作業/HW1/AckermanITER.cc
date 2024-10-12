# include <bits/stdc++.h>
using namespace std;

int ack(int, int);

int main(void){
    int m{0}, n{0};
    cin>>m>>n;
    cout<<ack(m, n)<<endl;
    return 0;
}

int ack(int m, int n){
    int Rec[100000]{0};         //最多接受 100000 層迴圈
    int reCnt{0};

    Rec[reCnt++] = m;           //記錄遞迴點 m 數值，並記錄遞迴次數
    while(reCnt > 0){           //遞迴到數
        m = Rec[--reCnt];       //每次遍歷一層遞迴
        if(m == 0) n++;
        else if(n == 0){
            Rec[reCnt++] = (m-1);   //進入下個迴圈，多一層，且紀錄 m
            n = 1;
        }
        else{
            Rec[reCnt++] = (m-1);
            Rec[reCnt++] = m;
            n--;
        }
    }
    return n;
}