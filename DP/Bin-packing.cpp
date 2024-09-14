/**
 * "Bin Packing" problem: n items of weights w[1]..w[n],
 * many bins of weight capacity W. Pack items into fewest number of bins.
 * Solution complexity: time O(2^n n^2), space O(2^n n).
 * Idea: for given set of items, firstly use as few bins as possible,
 *       secondly, fill the last used bin as little as possible. 
 * dp[mask] = {k,x} - k is min number of bins to pack mask items,
 *                    x is min used capacity of the last used bin.
*/

int n; ll W; cin >> n >> W;
vector<ll> w(n);
for(int i=0; i<n; ++i) cin >> w[i];

vector<pair<int,ll>> dp(1<<n);
dp[0] = {1,0};
for(int mask=1; mask<(1<<n); ++mask){
    dp[mask] = {n+1,0};
    for(int i=0; i<n; ++i){
        if(!((mask>>i)&1)) continue;
        auto [k,x] = dp[mask^(1<<i)];            
        if(x+w[i]<=W)
            dp[mask] = min(dp[mask], {k, x+w[i]});
        else
            dp[mask] = min(dp[mask], {k+1, w[i]});            
    }
}
cout << dp[(1<<n)-1].first << endl;
