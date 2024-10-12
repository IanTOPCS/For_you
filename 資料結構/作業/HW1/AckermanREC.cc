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
    if(m == 0) return (n+1);
    if(n == 0) return ack((m-1), 1);
    else{
        return ack((m-1), ack(m, (n-1)));
    }
}