/**
 * Algorithm to find all edge-2-connectivity components.
 * vertices: 1..n, edges: 0..m-1.
 * bridge[v] --- v is bridge.
 * comp[v] --- number of v's component.
 * Complexity: time -> O(n+m).
*/

int n, m; cin >> n >> m;
vector<vector<pair<int,int>>> g(n+1);
for(int e=0; e<m; ++e){
    int v,u; cin >> v >> u;
    g[v].push_back({u,e});
    g[u].push_back({v,e});
}

vector<int> up(n+1), d(n+1), comp(n+1);
vector<bool> used(n+1), bridge(n+1);

auto dfs = [&](int v, int e0, auto&& dfs)->void{
    used[v] = true; up[v] = d[v];
    for(auto [u, e] : g[v]){
        if(e == e0) continue;
        if(used[u])
            up[v] = min(up[v], d[u]);
        else{
            d[u] = d[v]+1;
            dfs(u, e, dfs);
            up[v] = min(up[v], up[u]);
            if(up[u] > d[v]){
                bridge[e] = true;
            }             
        }
    }
};

for(int v=1; v<=n; ++v)
    if(!used[v])
        dfs(v, -1, dfs);

auto paint = [&](int v, int col, auto&& paint)->void{
    used[v] = true; 
    comp[v] = col;
    for(auto [u,e] : g[v]){
        if(used[u] || bridge[e]) continue;
        paint(u, col, paint);
    }
}

used.assign(n+1, false);
for(int v=1; v<=n; ++v)
    if(!used[v]){
        ++k;
        paint(v, k, paint);
    }  


