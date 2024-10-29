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
        return gcd(b, a%b);     //在兩個都不為零，繼續輾轉相除法
    }
    return (a+b);               //在兩者未知誰為零，加起來即可
}
