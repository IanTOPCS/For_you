# include <bits/stdc++.h>
using namespace std;

int main(void){
  int n{0}, m{0};
  long long k{0};
  cin >> n >> m >> k;
  vector<vector<long long>> sor(n, vector<long long>(m, 0));
  for(int i = 0; i<n; i++){
    for(int j = 0; j<m; j++){
      cin>>sor[i][j];
    }
  }
  vector<vector<long long>> dp(n, vector<long long>(m, 0));
  for(int i = 0; i<n; i++){
    dp[i][(m-1)] = sor[i][(m-1)];
  }
  for(int j = (m-2); j>=0; j--){
    for(int i = 0; i<n; i++){
      int up = (i-1+n)%n;
      int down = (i+1)%n;
      dp[i][j] = min({dp[up][j+1], dp[down][j+1], dp[i][j+1]}) + sor[i][j];
    }
  }
  long long minCost = dp[0][0];
  for(int i = 1; i<n; i++){
    minCost = min(minCost, dp[i][0]);
  }
  if(minCost > k){
    cout<<"RE: START :<"<<endl;
  }
  else{
    cout<<minCost<<endl;
  }
  return 0;
}