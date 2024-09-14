/**
 * Dijkstra’s algorithm to find shortest distances.
 * vertices: 1..n.
 * Graph can be directed or undirected, with multiedges and loops.
 * Graph cannot contain NEGATIVE weights.
 * This should be used for DENSE graphs (m ~ n^2).
 * d[v] - distance to v from v0.
 * p[v] - previous vertex in a shortest path to v from v0.
 * Complexity: time -> O(n^2 + m).
*/

int n, m; cin >> n >> m;
vector<vector<pair<int,int>>> g(n+1); 
for(int i=0; i<m; ++i){
    int v,u,w; cin >> v >> u >> w;
    g[v].push_back({u,w});
    // g[u].push_back({v,w}); //for undirected graph
}

vector<ll> d(n+1, INF_LL); 
vector<int> p(n+1);
auto dijkstra = [&](int v0)->void{
    vector<bool> used(n+1);
    d[v0] = 0;
    for(int i=0; i<n; ++i){
        int v=0;
        for(int u=1; u<=n; ++u)
            if(!used[u] && (!v || d[u]<d[v]))
                v = u;
        used[v] = true;
        for(auto [u,w] : g[v])
            if(d[u] > d[v]+w){
                d[u] = d[v]+w;
                p[u] = v;
            }        
    }
};
