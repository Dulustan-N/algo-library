/**
 * Divide-and-Conquer DP Optimization - template.
 * dp[t][i] - i'th value of t'th layer of 2d DP, 
 * 1 <= t <= k, 1 <= i <= n.
 * DP transtion form: dp[t][i] = min_{j<i} dp[t-1][j] + c[j][i].
 * opt[t][i] - optimal j for dp[t][i].
 * Condition: opt[t][i] decreasing in i.
 * Complexity: O(kn log n).
*/

vector<vector<int>> dp(k+1, vector<int>(n+1,-INF));
vector<vector<int>> opt(k+1, vector<int>(n+1));

dp[0].assign(n+1,0);
for(int t=1; t<=k; ++t)
    dp[t][0] = 0;

auto calc = [&](int t, int l, int r, int cl, int cr, auto&& calc)->void{
    if(l>r) return;
    int m = (l+r)/2;        
    for(int i=cl; i<=min(m,cr); ++i){
        if(dp[t][m] < dp[t-1][i-1] + c[j][i]){
            dp[t][m] = dp[t-1][i-1] + c[j][i];
            opt[t][m] = i;
        }
    }
    calc(t, l, m-1, cl, opt[t][m], calc);
    calc(t, m+1, r, opt[t][m], cr, calc);
};
for(int t=1; t<=k; ++t)
    calc(t, 1, n, 1, n, calc);     
cout << dp[k][n] << endl;


//Answer recovery
vector<int> ans;
int t = k, i = n;
while(t){
    ans.push_back(opt[t][i]);
    --t; i = opt[t][i]-1;
}
reverse(ans.begin(), ans.end());    