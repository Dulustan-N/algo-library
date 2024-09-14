/**
 * Dijkstra’s algorithm to find shortest distances.
 * vertices: 1..n.
 * Graph can be directed or undirected, with multiedges and loops.
 * Graph cannot contain NEGATIVE weights.
 * This should be used for SPARSE graphs (m << n^2).
 * d[v] - distance to v from v0.
 * p[v] - previous vertex in a shortest path to v from v0.
 * This implementation uses sets.
 * Complexity: time -> O((n+m) log(n)).
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
    d[v0] = 0;
    set<pair<ll,int>> q; 
    q.insert({d[v0], v0});
    while(!q.empty()){
        int v = q.begin()->second;
        q.erase(q.begin());
        for(auto [u,w] : g[v]){
            if(d[u] > d[v] + w){
                q.erase({d[u], u});
                d[u] = d[v] + w;
                p[u] = v;
                q.insert({d[u], u});
            }
        }            
    }
};