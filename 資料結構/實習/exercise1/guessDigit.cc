#include <bits/stdc++.h>
using namespace std;

int main(void){
    cout<<"***�q�Ʀr�C��***"<<endl;
    cout<<"�п�J�Ʀr�d�� (0- ?):";
    int left{0};
    int right{-1};
    int cnt{0};
    while(right < left){
        cin>>right;
    }
    cout<<"---�n�F!�C���}�l---"<<endl;
    cout<<"�п�J�Ʀr�d�� (0-"<<right<<"):"<<endl;
    int guess{0};
    while(left != right){
        cout<<"�A�q���O�G";
        cin>>guess;
        if((guess < left) || (guess > right)){
            cout<<"..."<<endl;
            cnt++;
            continue;
        }
        else if((guess-left) >= (right-guess)){
            cout<<"�p�@�I"<<endl;
            right = guess-1;
            cnt++;
        }
        else if((guess-left) < (right-guess)){
            cout<<"�j�@�I"<<endl;
            left = guess+1;
            cnt++;
        }
    }
    while(1){
        cout<<"�A�q���O�G";
        cin>>guess;
        if(guess == left){
            cout<<"�A�q��F"<<endl;
            cnt++;
            cout<<"�`�@�q�F"<<cnt<<"��"<<endl;
            break;
        }
        else{
            cout<<"..."<<endl;
            cnt++;
        }
    }
    return 0;
}
