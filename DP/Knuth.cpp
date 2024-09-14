/**
 * Divide-and-Conquer DP Optimization - template.
 * dp[t][i] - i'th value of t'th layer of 2d DP, 
 * 1 <= t <= k, 1 <= i <= n.
 * DP transtion form: dp[t][i] = min_{j<i} dp[t-1][j] + c[j][i].
 * opt[t][i] - optimal j for dp[t][i].
 * Condition: opt[t][i] decreasing in i and increasing in t.
 * Complexity: O(kn).
*/

vector<vector<int>> dp(k+1, vector<int>(n+1,-INF));
vector<vector<int>> opt(k+1, vector<int>(n+1));
dp[0].assign(n+1,0); 
for(int t=1; t<=k; ++t)
    dp[t][0] = 0;

for(int t=1; t<=k; ++t){
    for(int i=n; i>0; --i){
        int l = t>1 ? opt[t-1][i] : 1;
        int r = i<n ? opt[t][i+1] : n;
        for(int j=l; j<=r; ++j)
            if(dp[t][n] < dp[t-1][i-1] + a[i] * (i-j+1)){
                dp[t][i] = dp[t-1][i-1] + a[i] * (i-j+1);
                opt[t][i] = j;
            } 
    }
}
cout << dp[k][n] << endl;


//Answer recovery
vector<int> ans;
int t = k, i = n;
while(t){
    ans.push_back(opt[t][i]);
    --t; i = opt[t][i]-1;
}
reverse(ans.begin(), ans.end());  