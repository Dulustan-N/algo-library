/**
 * Floyd-Warshall algorithm to find a cycle of negative weight.
 * vertices: 1..n.
 * Graph can be directed or undirected, with multiedges and loops.
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

int x = 0;
for(int k=1; k<=n && !x; ++k){
    for(int v=1; v<=n && !x; ++v){
        for(int u=1; u<=n & !x; ++u){
            if(d[v][k]<INF_LL && d[k][u]<INF_LL
            && d[v][u] > d[v][k]+d[k][u]){
                d[v][u] = max(d[v][k]+d[k][u], -INF_LL);
                p[v][u] = p[k][u];
            }
            if(v==u && d[v][v]<0)
                x = v;                
        }
    }
}
if(x==0){
    // No cycle. 
    return;
}

vector<int> cycle;
cycle.push_back(x);
for(int v=p[x][x]; v!=x; v=p[x][v])
    cycle.push_back(v);  
reverse(cycle.begin(), cycle.end());
