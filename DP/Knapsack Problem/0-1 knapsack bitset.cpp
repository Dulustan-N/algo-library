/**
 * "0-1 knapsack" problem:
 * n items with weights w[1]..w[n];
 * Optimal solution with bitset optimization.
 * fit max weight of items into knapsack of weight capacity W.
 * dp[i][x] - capacity x can be filled using only items 1..i (i is hidden).
 * Complexity: time -> O(nW / 64), space -> O(W).
*/

bitset<maxW> dp;
dp[0] = 1;
for(int i=1; i<=n; ++i){
    dp = dp | (dp << w[i]);
}
int ans=W;
while(!dp[ans])
    --ans;
cout << ans << endl;
