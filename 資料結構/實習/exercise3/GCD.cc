# include <bits/stdc++.h>
using namespace std;

int gcd(int, int);

int main(void){
    int a{0}, b{0};
    cin>>a>>b;
    cout<<gcd(a, b)<<endl;;
    return 0;
}

int gcd(int a, int b){
    if((a != 0) && (b != 0)){
        return gcd(b, a%b);     
    }
    return (a+b);               
}
