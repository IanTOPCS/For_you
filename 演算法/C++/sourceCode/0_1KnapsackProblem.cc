# include <bits/stdc++.h>
using namespace std;

int main(void){
  int objNum{0}, packWt{0}; cin>>objNum>>packWt;
  vector<int> objWt(objNum+1, 0), objVal(objNum+1, 0);
  vector<vector<int>> dp(objNum+1, vector<int>(packWt+1, 0));
  for(int i = 1; i<=objNum; i++){
    cin>>objWt[i]>>objVal[i];
  }
  for(int obj = 1; obj<=objNum; obj++){
    for(int wt = 1; wt<=packWt; wt++){
      if(objWt[obj] <= wt){
        // Judge the max value between choose(last status(Suppose I choose, the room still available is "wt - objwt[obj]") + this object value) and not choose(last status)
        dp[obj][wt] = max(dp[obj-1][wt], (dp[obj-1][wt-objWt[obj]] + objVal[obj]));
      }
      else{
        // Keep it as same as not choose the object(not had enough room to put object)
        dp[obj][wt] = dp[obj-1][wt];
      }
    }
  }
  // The max value of 0/1 pack when have objNum object with limit of packWt
  cout<<dp[objNum][packWt]<<endl;
  // deal with record of max value in 0/1 pack
  // vector<int> packRecord;
  // while((objNum > 0) && (packWt > 0)){
  //   if(dp[objNum][packWt] != dp[objNum-1][packWt]){
  //     packRecord.push_back(objNum);
  //     packWt-=objWt[objNum];
  //     objNum--;
  //   }
  //   else{
  //     objNum--;
  //   }
  // }
  // reverse(packRecord.begin(), packRecord.end());
  // for(auto x : packRecord) cout<<x<<" ";
  // cout<<endl;
  return 0;
}

/*
4 8
2 1
3 2
4 5
5 6
*/
/*
8
*/