# include <bits/stdc++.h>
using namespace std;

int fab(int);

int main(void){
    int index{0};
    cin>>index;
    cout<<fab(index-1)<<endl;
    return 0;
}

int fab(int index){
    if(index <= 1) return index;            //initial cases, if 0 return 0, if 1 return 1
    return fab(index-1) + fab(index-2);     //fabonacci formula
}