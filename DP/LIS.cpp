/**
 * Longest Increasing Sequence (LIS) problem: 
 * given array a[0]..a[n-1], find LIS.
 * dp[l] - min a[i] such that LIS of length l ends in a[i].
 * id[l] - index of last element of LIS dp[l].
 * p[l] - previous to last element of LIS dp[l].
 * Complexity: time -> O(n log n), space -> O(n).
*/

// only length of LIS
auto lis = [](const vector<int> &a)->int{
    int n = a.size();
    vector<int> dp(n+1, INF); dp[0] = -INF;
    int len=0;
    for(int i=0; i<n; ++i){
        int l=lower_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        dp[l] = a[i];
        if(dp[l] < INF) len = max(len, l);
    }    
    return len;
};


// full LIS
auto lis = [](const vector<int> &a)->vector<int>{
    int n = a.size();
    vector<int> dp(n+1, INF), id(n+1), p(n+1); 
    dp[0] = -INF; id[0] = -1;
    int len=0;
    for(int i=0; i<n; ++i){
        int l=lower_bound(dp.begin(),dp.end(),a[i]) - dp.begin();
        dp[l] = a[i];
        id[l] = i;
        p[i] = id[l-1];            
        if(dp[l] < INF) len = max(len, l);        
    }

    vector<int> ans;
    int i = id[len];
    while(i != -1){
        ans.push_back(a[i]);
        i = p[i];
    } 
    reverse(ans.begin(), ans.end());   
    return ans;
};

