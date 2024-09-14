/**
 * Graph input and simple DFS on it
 * 1-based indexation for vertices.
*/

int n, m; cin >> n >> m;
vector<vector<int>> g(n+1); 
vector<bool> used(n+1);
for(int i=0; i<m; ++i){
    int v, u; cin >> v >> u;
    g[v].push_back(u);
    g[u].push_back(v);
}
auto dfs = [&](int v, auto&& dfs){
    cout << "Enter " << v << endl;
    used[v] = true;
    for(auto u : g[v])
        if(!used[u])        
            dfs(u);
    cout << "Exit " << v << endl;
}


