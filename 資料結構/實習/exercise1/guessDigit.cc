#include <bits/stdc++.h>
using namespace std;

int main(void){
    cout<<"***猜數字遊戲***"<<endl;
    cout<<"請輸入數字範圍 (0- ?):";
    int left{0};
    int right{-1};
    int cnt{0};
    while(right < left){
        cin>>right;
    }
    cout<<"---好了!遊戲開始---"<<endl;
    cout<<"請輸入數字範圍 (0-"<<right<<"):"<<endl;
    int guess{0};
    while(left != right){
        cout<<"你猜的是：";
        cin>>guess;
        if((guess < left) || (guess > right)){
            cout<<"..."<<endl;
            cnt++;
            continue;
        }
        else if((guess-left) >= (right-guess)){
            cout<<"小一點"<<endl;
            right = guess-1;
            cnt++;
        }
        else if((guess-left) < (right-guess)){
            cout<<"大一點"<<endl;
            left = guess+1;
            cnt++;
        }
    }
    while(1){
        cout<<"你猜的是：";
        cin>>guess;
        if(guess == left){
            cout<<"你猜對了"<<endl;
            cnt++;
            cout<<"總共猜了"<<cnt<<"次"<<endl;
            break;
        }
        else{
            cout<<"..."<<endl;
            cnt++;
        }
    }
    return 0;
}
