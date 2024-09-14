/**
 * Algorithm to find all articulation points.
 * vertices: 1..n, edges: 0..m-1.
 * Graph can have loops and multiedges.
 * Complexity: time -> O(n+m).
*/

int n, m; cin >> n >> m;
vector<vector<pair<int,int>>> g(n+1);
for(int e=0; e<m; ++e){
    int v,u; cin >> v >> u;
    g[v].push_back({u,e});
    g[u].push_back({v,e});
}

vector<bool> used(n+1);
vector<int> up(n+1), d(n+1);

auto dfs = [&](int v, int e0, auto&& dfs)->void{
    used[v] = true; up[v] = d[v];
    int ch=0;
    for(auto [u,e] : g[v]){
        if(e==e0) continue;
        if(used[u])
            up[v] = min(up[v], d[u]);
        else{
            d[u] = d[v] + 1;
            dfs(u,e,dfs);
            up[v] = min(up[v], up[u]);
            if(up[u]>=d[v] && d[v]>0){
                //v - articulation point
            }
            ++ch;
        }
    }
    if(d[v]==0 && ch>1){
        //v - articulation point
    }
};

for(int v=1; v<=n; ++v)
    if(!used[v])
        dfs(v, -1, dfs);


