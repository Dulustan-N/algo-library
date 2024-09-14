/**
 * Centroid Decomposition example.
 * Problem: Count paths of fixed length k in a tree.
 * vertices: 1..n.
 * dfs_sz - calculates size of a centroid component.
 * cen - finds centroid of a component.
 * build - builds the centroid decomposition in O(n log n). 
 * Complexity: time -> O(n log n).
*/

vector<int> s(n+1), p(n+1);
vector<bool> used(n+1);
auto dfs_sz = [&](int v, int v0, auto&& dfs_sz)->void{
    s[v] = 1;
    for(auto u : g[v]){
        if(u==v0 || used[u]) continue;
        dfs_sz(u, v, dfs_sz);
        s[v] += s[u];
    }
};

auto cen = [&](int v, int v0, int n, auto&& cen)->int{
    for(auto u : g[v]){
        if(u==v0 || used[u]) continue;
        if(s[u] > n/2)
            return cen(u, v, n, cen);
    }
    return v;
};    

ll ans=0;
auto build = [&](int v, int c0, auto&& build)->void{
    dfs_sz(v, 0, dfs_sz);
    int c = cen(v, 0, s[v], cen);
    p[c] = c0;
    used[c] = true;   
    
    //Count paths of length k    
    vector<int> dep;
    vector<int> cnt(s[v]); cnt[0] = 1;
    auto dfs = [&](int v, int v0, int d, auto&& dfs)->void{
        dep.push_back(d);
        for(auto u : g[v]){
            if(u==v0 || used[u]) continue;
            dfs(u, v, d+1, dfs);
        }
    };

    for(auto u : g[c]){
        if(used[u]) continue;
        dep.clear();
        dfs(u, c, 1, dfs);
        for(auto d : dep)
            if(k-d>=0 && k-d<cnt.size())
                ans += cnt[k-d];
        for(auto d : dep)
            ++cnt[d];
    }         
    for(auto u : g[c])
        if(!used[u])
            build(u, c, build);
};

build(1, 0, build); 
