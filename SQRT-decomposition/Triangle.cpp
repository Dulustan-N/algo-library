/**
 * Problem: count a number of triangles (cycles of length 3) in a graph.
 */

int n,m; cin >> n >> m;
vector<vector<int>> g(n+1);
vector<int> deg(n+1);
vector<pair<int,int>> edge(m);
for(int i=0; i<m; ++i){
    int v,u; cin >> v >> u;
    if(v>u) swap(v,u);
    edge[i] = {v,u};
    ++deg[v]; ++deg[u];
}
for(auto [v,u] : edge){
    if(deg[v]<=deg[u])
        g[v].push_back(u);
    else
        g[u].push_back(v);
}

int ans=0;
vector<int> used(n+1);
for(int v=1; v<=n; ++v){
    for(auto u : g[v])
        used[u] = v;
    for(auto u : g[v]){
        for(auto w : g[u])
            if(used[w]==v)
                ++ans;
    }
}
cout << ans << endl;
