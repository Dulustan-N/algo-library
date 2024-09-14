/**
 * Digit DP example.
 * Problem: count the number of integers between a and b 
 * where no two adjacent digits are the same.
 * Solution complexity: O(len(max(a,b)) * 100).
 * dp[i][t][x] - number of numbers (with no leading zeroes) of length i+1  and last digit x;
 * t = 0 - numbers exactly coincide with a prefix of n.
 * t = 1 - some prefix of these nubmers is less than prefix of n.
 * digit_dp(N) - counts number of good numbers in [1, N] by dividing it into
 *             ranges 0, [1, 9], [10, 99], .., [10..0, N].
 * digit(N) - calculates answer for one of those ranges.
*/

ll a,b; cin >> a >> b;
string L = to_string(a-1), R = to_string(b);

auto digit = [](string N)->ll{
    int n = N.size();
    vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(2, vector<ll>(10)));
    for(int d=1; d<N[0]-'0'; ++d) 
        dp[0][1][d] = 1;
    dp[0][0][N[0]-'0'] = 1;
    for(int i=1; i<n; ++i){
        if(N[i-1]!=N[i])
            dp[i][0][N[i]-'0'] += dp[i-1][0][N[i-1]-'0'];
        for(int x=0; x<N[i]-'0'; ++x)
            if(x!=N[i-1]-'0')
                dp[i][1][x] += dp[i-1][0][N[i-1]-'0'];
        for(int x=0; x<10; ++x)
            for(int y=0; y<10; ++y)
                if(x!=y)
                    dp[i][1][x] += dp[i-1][1][y];                
    }
    ll ans=0;
    for(int x=0; x<10; ++x)
        ans += dp[n-1][0][x] + dp[n-1][1][x];
    return ans;
};

auto digit_dp = [&](string N)->ll{
    if(N=="-1") return 0;
    if(N=="0") return 1;
    ll ans=1;
    string cur;
    for(int i=0; i<N.size()-1; ++i){
        cur.push_back('9');
        ans += digit(cur);
    }
    ans += digit(N);
    return ans;
};

cout << digit_dp(R) - digit_dp(L) << endl;
