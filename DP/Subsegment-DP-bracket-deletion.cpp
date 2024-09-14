/**
 * Subsegment DP example.
 * Problem: string s of length n consisting of only [,],{,},(,).
 * Delete min number of brackets to make s  Correct Bracket Sequence.
 * dp[l][r] - min number of brackets to make s[l..r-1] CBS.
 * get(l,r) - recursive recovery of answer.
 * Complexity: time -> O(n^3), space -> O(n^2).
*/

vector<vector<int>> dp(n, vector<int>(n+1, INF));
vector<vector<int>> p(n, vector<int>(n+1));
for(int l=0; l<n; ++l){
    dp[l][l+1] = 1;
    dp[l][l] = 0;
}    
for(int len=1; len<=n; ++len){
    for(int l=0,r=len; r<=n; ++l,++r){
        if((s[l]=='(' && s[r-1]==')')
        || (s[l]=='[' && s[r-1]==']')
        || (s[l]=='{' && s[r-1]=='}') ){
            dp[l][r] = dp[l+1][r-1];
            p[l][r] = r;
        }
        for(int m=l+1; m<r; ++m)
            if(dp[l][r] > dp[l][m] + dp[m][r]){
                dp[l][r] = dp[l][m] + dp[m][r];
                p[l][r] = m;
            }                
    }    
}
cout << dp[0][n] << endl;


// Answer recovery
auto get = [&](int l, int r, auto&& get)->string{
    if(p[l][r] == 0) return "";
    if(p[l][r] == r) 
        return s[l] + get(l+1,r-1) + s[r-1];
    return get(l, p[l][r], get) + get(p[l][r], r, get);    
}
cout << get(0,n) << endl;

