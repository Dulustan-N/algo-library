/**
 * Kosaraju algorithm to find strongly connected components (SCC).
 * vertices: 1..n.
 * gt - transposed graph to g.
 * gc - condensed graph.
 * Complexity: time -> O(n+m).
*/

int n, m; cin >> n >> m;
vector<vector<int>> g(n+1), gt(n+1);
for(int i=0; i<m; ++i){
    int v,u; cin >> v >> u;
    g[v].push_back(u);
    gt[u].push_back(v);
}

vector<bool> used(n+1);
vector<int> tsort;
auto dfs0 = [&](int v, auto&& dfs0)->void{
    used[v] = true;
    for(auto u : g[v]){
        if(!used[u])
            dfs0(u, dfs0);
    }               
    tsort.push_back(v);
};

for(int v=1; v<=n; ++v)
    if(!used[v])
        dfs0(v, dfs0);
reverse(tsort.begin(), tsort.end());

vector<int> scc(n+1);
int cnt=0;
auto dfs1 = [&](int v, auto&& dfs1)->void{
    scc[v] = cnt;
    for(auto u : gt[v])
        if(!scc[u])
            dfs1(u, dfs1);
};

for(auto v : tsort){
    if(!scc[v]){
        ++cnt;
        dfs1(v, dfs1);
    }
}

//Graph Condensation
vector<vector<int>> gc(cnt+1);
vector<int> vis(cnt+1);
for(int v=1; v<=n; ++v){
    for(auto u : g[v])
        if(scc[u]!=scc[v] && vis[scc[u]]!=scc[v]){
            gc[scc[v]].push_back(scc[u]);
            vis[scc[u]] = scc[v];
        }
} 
