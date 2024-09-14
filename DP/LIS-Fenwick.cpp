/**
 * Longest Increasing Sequence (LIS) problem: 
 * given array a[0]..a[n-1], find LIS.
 * dp[i] - length of LIS of a[0]..a[i] that ends in a[i].
 * Complexity: time -> O(n log n), space -> O(n log n).
*/

//only length
struct Fenwick{
    vector<int> t;
    Fenwick(int n){
        t.resize(n+1);
    }
    void upd(int i, int v){
        for(; i<t.size(); i+=i&(-i))
            t[i] = max(t[i], v);
    }    
    int get(int i){
        int res=0;
        if(i==0) return 0;
        for(; i>0; i-=i&(-i))
            res = max(res, t[i]);
        return res;
    }
};

auto lis = [](const vector<int> &a)->int{
    int n = a.size();
    vector<int> dp(n);
    Fenwick scan(n+1);
    for(int i=0; i<n; ++i){
        auto x = scan.get(a[i]-1);
        dp[i] = x + 1;
        scan.upd(a[i], dp[i]);
    }    
    return scan.get(n);
};


//with full answer
struct Fenwick{
    vector<pair<int,int>> t;
    Fenwick(int n){
        t.resize(n+1,{0,-1});
    }
    void upd(int i, pair<int,int> v){
        for(; i<t.size(); i+=i&(-i))
            t[i] = max(t[i], v);
    }    
    pair<int,int> get(int i){
        if(i==0) return {0,-1};
        pair<int,int> res={0,-1};
        for(; i>0; i-=i&(-i))
            res = max(res, t[i]);
        return res;
    }
};

auto lis = [](const vector<int> &a)->vector<int>{
    int n = a.size();
    vector<int> dp(n), p(n);
    Fenwick scan(n+1);
    for(int i=0; i<n; ++i){
        auto [x,j] = scan.get(a[i]-1);
        dp[i] = x + 1;
        p[i] = j;
        scan.upd(a[i], {dp[i],i});
    }    
    vector<int> ans;
    int i = scan.get(n+1).S;
    while(i!=-1){
        ans.push_back(a[i]);
        i = p[i];
    }
    reverse(ans.begin(), ans.end());    
    return ans; 
};

