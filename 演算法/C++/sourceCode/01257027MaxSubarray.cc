# include <bits/stdc++.h>
using namespace std;

int maxSum(int *nums = nullptr, int len = 0);

int main(void){
    int howMany{0};
    cin>>howMany;
    int *nums = new int[howMany];
    for(int i = 0; i<howMany; i++){
        cin>>nums[i];
    }
    cout<<maxSum(nums, howMany)<<"\n";
    delete[] nums;
    return 0;
}

int maxSum(int *nums, int len){
    int maxNow{0};
    int maxBefore{INT_MIN};                 // 考慮負數
    for(int i = 0; i<len; i++){
        maxNow += nums[i];
        if(maxBefore < maxNow){
            maxBefore = maxNow;
        }
        if (maxNow < 0) maxNow = 0;
        // cout<<i<<":"<<maxBefore<<endl; // debug
    }
    return maxBefore;
}

/*
4
1 2 3 4
*/