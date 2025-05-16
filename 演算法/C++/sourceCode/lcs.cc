# include <bits/stdc++.h>
using namespace std;
// This problem is about find same chars in two string.
// Use DP algorithm, using n^2 table to record chars that as same as another string (now length, not total lenght of string)
// key: If two char you focus is the same, find the DP table and plus one; Else choose max number in DP table without this char.
int lcs(const vector<int> &a, const vector<int> &b){
  int n = a.size(), m = b.size();
  vector<vector<int>> dp(n+1, vector<int>(m+1, 0)); // 表格i, j表示兩字串的第i, j個字元
  for(int i =1; i<=n; i++){
    for(int j = 1; j<=m; j++){
      if(a[i-1] == b[j-1]){
        dp[i][j] = dp[i-1][j-1]+1;  // 關注的兩個字元相同，左上角數字+1
      }
      else{
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]); // 選擇跳過字元i或j，保持最大子字串，選擇較大者
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