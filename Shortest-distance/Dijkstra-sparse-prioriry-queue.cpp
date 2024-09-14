/**
 * Dijkstra’s algorithm to find shortest distances.
 * vertices: 1..n.
 * Graph can be directed or undirected, with multiedges and loops.
 * Graph cannot contain NEGATIVE weights.
 * This should be used for SPARSE graphs (m << n^2).
 * d[v] - distance to v from v0.
 * p[v] - previous vertex in a shortest path to v from v0.
 * This implementation uses priority_queue.
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
    priority_queue<pair<ll,int>> q; 
    q.push({-d[v0], v0});
    while(q.size()){
        auto [x,v] = q.top();
        q.pop();
        if(x != -d[v]) continue;
        for(auto [u,w] : g[v]){
            if(d[u] > d[v] + w){                
                d[u] = d[v] + w;
                p[u] = v;
                q.push({-d[u], u});
            }
        }            
    } 
};