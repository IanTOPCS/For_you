#include <bits/stdc++.h>
using namespace std;

int fab(int);

int main(void){
    int index{0};
    cin>>index;
    cout<<fab(index)<<endl;
    return 0;
}

int fab(int index){
    if(index == 1) return 0;                        //init case
    else if(index == 2) return 1;                   //init case
    pair<int, int> sor;                             //use pair to store the last two numbers
    sor.first = 0, sor.second = 1;
    for(int i = 3; i<=index; i++){
        int temp = sor.second;                      //next round first number is second number at now
        sor.second = sor.first + sor.second;        //store new number（answer）to second number
        sor.first = temp;                           //store temp to first number for next round
    }
    return sor.second;                              //return fabnocci-number for the given index
}