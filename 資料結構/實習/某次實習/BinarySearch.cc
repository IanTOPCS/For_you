# include <bits/stdc++.h>
using namespace std;

int bs(int*, int, int, int);

int main(void){
    int search{0};cin>>search;
    int num{0};cin>>num;
    int *sor = new int[num];
    for(int i = 0; i<num; i++){
        cin>>sor[i];
    }
    cout<<bs(sor, 0, num-1, search)<<endl;
    return 0;
}

int bs(int *sor, int left, int right, int tar){
    if(left <= right){
        int mid = ceil((left+right)/2);
        if(sor[mid] == tar){
            return mid;
        }
        else if(sor[mid] > tar){
            return bs(sor, left, (mid-1), tar);
        }
        else{
            return bs(sor, (mid+1), right, tar);
        }
    }
    return -1;
}

/*
1
15
3 11 15 20 23 29 31 35 36 43 47 49 50 53 56
*/
