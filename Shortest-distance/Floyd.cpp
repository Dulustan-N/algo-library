/**
 * Floyd-Warshall algorithm to find all shortest distances in a graph.
 * vertices: 1..n.
 * Graph can be directed or undirected, with multiedges and loops.
 * Graph can contain NEGATIVE weights.
 * d[v] - distance to v from v0.
 * p[v] - previous vertex in a shortest path to v from v0.
 * Complexity: time -> O(n^3).
*/

vector<vector<pair<int,int>>> g(n+1);
vector<vector<ll>> d(n+1, vector<ll>(n+1,INF_LL)); 
vector<vector<int>> p(n+1, vector<int>(n+1));
for(int i=0; i<m; ++i){
    int v,u; ll w; cin >> v >> u >> w;
    g[v].push_back({u,w});
    g[u].push_back({v,w});
    d[v][u] = min(d[v][u], w);
    d[u][v] = min(d[u][v], w);
}    
for(int v=1; v<=n; ++v)
    d[v][v] = 0;

for(int k=1; k<=n; ++k){
    for(int v=1; v<=n; ++v){
        for(int u=1; u<=n; ++u){
            if(d[v][k]<INF_LL && d[k][u]<INF_LL
            && d[v][u] > d[v][k]+d[k][u]){
                d[v][u] = max(d[v][k]+d[k][u], -INF_LL);
                p[v][u] = p[k][u];
            }
        }
    }
}

// Restore path v -> u
vector<int> path;
path.push_back(u);
while(u != v){
    u = p[v][u];
    path.push_back(u);
}
reverse(path.begin(), path.end());

