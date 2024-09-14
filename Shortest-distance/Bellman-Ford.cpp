/**
 * Bellman-Ford algorithm to find shortest distances.
 * vertices: 1..n.
 * Graph can be directed or undirected, with multiedges and loops.
 * Graph can contain NEGATIVE weights.
 * d[v] - distance to v from v0.
 * p[v] - previous vertex in a shortest path to v from v0.
 * Complexity: time -> O(nm).
*/

struct Edge{
    int v, u, w;
};
int n, m; cin >> n >> m;
vector<Edge> edge(m);
for(int i=0; i<m; ++i){
    int v,u,w; cin >> v >> u >> w;
    edge[i] = {v,u,w};
}

vector<ll> d(n+1, INF_LL); 
vector<int> p(n+1);
auto bellman = [&](int v0)->void{
    d[v0] = 0;
    for(int t=0; t<n-1; ++t){
        for(auto [v,u,w] : edge)
            if(d[v]<INF_LL && d[v]+w<d[u]){
                d[u] = d[v]+w;
                p[u] = v;
            }
    } 
};

