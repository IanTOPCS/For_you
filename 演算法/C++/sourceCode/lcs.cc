# include <bits/stdc++.h>
using namespace std;

int lcs(const vector<int> &a, const vector<int> &b){
  int n = a.size(), m = b.size();
  vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
  for(int i =1; i<=n; i++){
    for(int j = 1; j<=m; j++){
      if(a[i-1] == b[j-1]){
        dp[i][j] = dp[i-1][j-1]+1;
      }
      else{
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }
    }
  }
  return dp[n][m];
}

int main(void){
  int n{0}, m{0};
  cin >> n >> m;
  vector<int> a, b;
  for(int i = 0; i<n; i++){
    int x{0};
    cin>> x;
    a.push_back(x);
  }
  for(int i = 0; i<n; i++){
    int x{0};
    cin>> x;
    b.push_back(x);
  }
  int ans = lcs(a, b);
  cout << ans;
  if (ans > ceil(b.size()/2)){
    cout<<" Yes"<<endl;
  }
  else{
    cout<<" No"<<endl;
  }
  return 0;
}