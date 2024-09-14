/**
 * DP on Broken Profile example.
 * Problem: Count number of tilings of n x m field by 1 x 2 tiles.
 * dp[i][j][p] - number of tilings of first i-1 columns and 
 *              first j cells of i-th column, with a profile p.
 * Answer is dp[m][n][0].
 * Complexity: time - O(nm 2^n), space - O(nm 2^n).
*/

int n,m; cin >> n >> m;
if(n>m) swap(n,m);
vector<vector<vector<int>>> dp(m+1, vector<vector<int>>(n+1, vector<int>(1<<n)));
dp[0][n][0] = 1;
for(int i=1; i<=m; ++i){
    for(int p=0; p<(1<<n); ++p)
        dp[i][0][p] = dp[i-1][n][p];
    for(int j=1; j<=n; ++j){
        for(int p=0; p<(1<<n); ++p){
            if((p>>j-1)&1) 
                dp[i][j][p] = dp[i][j-1][p^(1<<j-1)];
            else{
                dp[i][j][p] = dp[i][j-1][p|(1<<j-1)];
                if(j>1 && !((p>>j-2)&1))
                    dp[i][j][p] = (dp[i][j][p] + dp[i][j-2][p]) % M;   
            }
        }
    }
}
cout << dp[m][n][0] << endl;
