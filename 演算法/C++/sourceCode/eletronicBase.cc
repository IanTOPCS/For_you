# include <bits/stdc++.h>
using namespace std;

bool canCover(vector<long long> &sor, long long k, long long midDis){
    long long cnt{0}, index{0};
    while(index < sor.size()){
        cnt++;
        long long coverStart = sor[index];
        long long coverEnd = coverStart + midDis;
        while(index < sor.size() && sor[index] <= coverEnd){
            index++;
        }
    }
    return cnt <= k;
}

long long findMinRequire(vector<long long> &sor, long long k){
    sort(sor.begin(), sor.end());
    long long minDis{1};
    long long maxDis = sor.back() - sor.front();
    long long resultDis = maxDis;
    while(minDis <= maxDis){
        long long midDis = (minDis + maxDis) / 2;
        if(canCover(sor, k, midDis)){
            resultDis = midDis;
            maxDis = midDis - 1;
        }
        else{
            minDis = midDis + 1;
        }
    }
    return resultDis;
}

int main(void){
    long long n{0}, k{0};
    cin>>n>>k;
    vector<long long> sor(n, 0);
    for(int i = 0; i<n; i++){
        cin>>sor[i];
    }
    long long minRequire = findMinRequire(sor, k);
    cout<<minRequire<<endl;
    return 0;
}