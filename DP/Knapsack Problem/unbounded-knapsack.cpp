/**
 * "Unbounded knapsack with costs" problem:
 * n items with weights w[1]..w[n] and costs c[1]..c[n], 
 * each item has infinite duplicates.
 * fit max cost of items into knapsack of weight capacity W.
 * p[i][x] - max cost of items if using only 1..i 
 *          and exact weight of items is x (i may be hidden parameter).
 * Complexity: time -> O(nW), space -> O(W).
*/

vector<int> dp(W+1);
for(int i=1; i<=n; ++i){
    for(int x=0; x<=W; ++x){
        if(dp[x-w[i]] != -INF)
            dp[x] = max(dp[x], c[i] + dp[x-w[i]]);
    }    
}

int ans=0;
for(int x=1; x<=W; ++x)
    ans = max(ans, dp[x]);

