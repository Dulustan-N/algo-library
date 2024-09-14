/**
 * Lowest common ancestor (LCA) by Tarjan algorithm.
 * Answers all queries OFFLINE in O(n+Q).
 * vertices: 1..n, queries: 0..Q-1.
 * q[v] = {u, i} - v has a query (number i) of LCA with u.
 * lca[i] - answer of LCA to query i.
 * Complexity: time -> O(n+Q).
*/

//DSU
vector<int> p(n+1), s(n+1,1);
for(int v=1; v<=n; ++v) p[v] = v;
auto root = [&](int v, auto&& root)->int{
    if(v!=p[v])
        p[v] = root(p[v], root);     
    return p[v];
};
auto unite = [&](int v, int u)->void{
    v = root(v, root);
    u = root(u, root);
    if(v==u) return;
    if(s[v]<s[u]) swap(v,u);
    p[u] = v;
    s[v] += s[u];    
};

//Tarjan    
vector<int> anc(n+1), lca(Q);   
vector<bool> used(n+1); 
vector<vector<pair<int,int>>> q(n+1);
for(int i=0; i<Q; ++i){
    int v,u; cin >> v >> u;
    q[v].push_back({u,i});   
    q[u].push_back({v,i});  
}

auto dfs = [&](int v, int v0, auto&& dfs)->void{
    p[v] = v; s[v] = 1; anc[v] = v;
    for(auto u : g[v]){
        if(u==v0) continue;
        dfs(u,v,dfs);
        unite(v,u);
        anc[root(v,root)] = v; 
    }
    used[v] = true;
    for(auto [u,i] : q[v])
        if(used[u])
            ans[i] = anc[root(u,root)];
};
dfs(1,0,dfs);

for(auto v : lca)
    cout << v << "\n";  
