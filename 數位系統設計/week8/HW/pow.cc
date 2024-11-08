# include <bits/stdc++.h>
using namespace std;

int main(void){
    ofstream file;
    file.open("./myPow.txt");
    for (int i = 0; i < 256; i++){
        file<<i<<" : "<<pow(i, 2)<<endl;
    }
    return 0;
}