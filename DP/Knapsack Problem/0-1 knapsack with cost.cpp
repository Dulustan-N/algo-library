/**
 * "0-1 knapsack with costs" problem:
 * n items with weights w[1]..w[n] and costs c[1]..c[n];
 * fit max cost of items into knapsack of weight capacity W.
 * dp[i][x] - max cost of items if using only 1..i 
 *          and exact weight of items is x (i may be hidden parameter).
 * pick[i][x] - item i is picked in dp[i][x].
 * Complexity: time -> O(nW), space -> O(W) / O(nW).
*/

// O(W) memory, no answer recovery.
vector<int> dp(W+1,-INF);
dp[0] = 0;
for(int i=1; i<=n; ++i)
    for(int x=W; x>=w[i]; --x)
        if(dp[x-w[i]] != -INF)
            dp[x] = max(dp[x], dp[x-w[i]] + c[i]);
        
int ans=0;
for(int x=1; x<=W; ++x)
    ans = max(ans, dp[x]);


// O(nW) memory with answer recovery
vector<vector<int>> dp(n+1, vector<int>(W+1,-INF));
vector<vector<bool>> pick(n+1, vector<bool>(W+1));
dp[0][0] = 0;
for(int i=1; i<=n; ++i){
    for(int x=0; x<=W; ++x){        
        dp[i][x] = dp[i-1][x];
        pick[i][x] = 0;
        if(x>=w[i] && dp[i-1][x-w[i]]!=-INF
        && dp[i-1][x-w[i]]+c[i] > dp[i][x]){
            dp[i][x] = dp[i-1][x-w[i]]+c[i];
            pick[i][x] = 1;
        }
    }
}
vector<int> ans;
int x=0;
for(int t=1; t<=W; ++t)
    if(dp[n][t] > dp[n][x])
        x = t;
for(int i=n; i>0; --i){
    if(pick[i][x]){
        ans.push_back(i);
        x -= w[i];
    }
}
reverse(ans.begin(), ans.end());


// answer recovery without choice memory
vector<int> ans;
int x=0;
for(int t=1; t<=W; ++t)
    if(dp[n][t] > dp[n][x])
        x = t;
for(int i=n; i>0; --i){
    if(dp[i][x] == dp[i-1][x] + c[i]){
        ans.push_back(i);
        x -= w[i];
    }
}
reverse(ans.begin(), ans.end());
