/**
 * Sum-over-subsets DP (SOS DP) example.
 * Problem: A[x] for x = 0..2^n-1 -- value for each mask of n elements.
 * Calculate dp[mask] = sum of all A[subm] such that subm is submask of mask, for each mask.
 * Complexity -> O(n 2^n).
 */

for(int mask=0; mask<(1<<N); ++mask)
    dp[mask] = A[mask];
for(int i=0; i<n; ++i) 
    for(int mask=0; mask<(1<<n); ++mask)
        if((mask>>i)&1)
            dp[mask] += dp[mask^(1<<i)];


/**
 * Problem: f[x] = 1 for some masks x in [0..2^n-1]. For each f[mask] = 1
 * make f[subm] = 1 for all subm that is submask of mask.
 * Complexity -> O(n 2^n).
 */

for(int mask=(1<<n)-1; mask>0; --mask){
    if(!f[mask]) continue;
    for(int i=0; i<n; ++i)
        if((mask>>i)&1)
            f[mask^(1<<i)] = 1;            
}