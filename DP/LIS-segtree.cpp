/**
 * Longest Increasing Sequence (LIS) problem: 
 * given array a[0]..a[n-1], find LIS.
 * dp[i] - length of LIS of a[0]..a[i] that ends in a[i].
 * Complexity: time -> O(n log n), space -> O(n log n).
*/

// only length of LIS
struct SegTree{
    vector<int> t;
    int n;
    SegTree(int n) : n(n){t.resize(2*n);}
    void upd(int p, int v){
        p += n;
        t[p] = v;
        for(p/=2; p>0; p/=2)
            t[p] = max(t[2*p], t[2*p+1]);
    }
    auto get(int l, int r){
        int res = 0;        
        for(l+=n, r+=n; l<r; l/=2, r/=2){
            if(l&1) res = max(res, t[l++]);
            if(r&1) res = max(res, t[--r]);
        }
        return res;
    }   
};

auto lis = [](const vector<int> &a)->int{
    int n = a.size(), m;
    auto co = a;
    sort(co.begin(), co.end());
    m = unique(co.begin(), co.end()) - co.begin();
    co.resize(m);
    SegTree scan(m);
    for(int i=0; i<n; ++i){
        int x = lower_bound(co.begin(), co.end(), a[i]) - co.begin();
        auto len = scan.get(0, x);
        scan.upd(x, len+1);
    }    
    return scan.get(0, m);
};   


// full LIS
struct SegTree{
    vector<pair<int,int>> t;
    int n;
    SegTree(int n) : n(n){t.resize(2*n, {0,-1});}
    void upd(int p, pair<int,int> v){
        p += n;
        t[p] = v;
        for(p/=2; p>0; p/=2)
            t[p] = max(t[2*p], t[2*p+1]);
    }
    auto get(int l, int r){
        pair<int,int> res = {0,-1};        
        for(l+=n, r+=n; l<r; l/=2, r/=2){
            if(l&1) res = max(res, t[l++]);
            if(r&1) res = max(res, t[--r]);
        }
        return res;
    }   
};

auto lis = [](const vector<int> &a)->vector<int>{
    int n = a.size(), m;
    auto co = a; 
    sort(co.begin(), co.end());
    m = unique(co.begin(), co.end()) - co.begin();
    co.resize(m);

    vector<int> p(n);
    SegTree scan(m);
    for(int i=0; i<n; ++i){
        int x = lower_bound(co.begin(), co.end(), a[i]) - co.begin();
        auto [len, j] = scan.get(0, x);
        p[i] = j;
        scan.upd(x, {len+1, i});
    }    
    vector<int> ans;
    int i = scan.get(0, m).second;
    while(i != -1){
        ans.push_back(a[i]);
        i = p[i];
    }
    reverse(ans.begin(), ans.end());
    return ans;    
}; 