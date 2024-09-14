/**
 * Bellman-Ford algorithm to find shortest paths in graph.
 * vertices: 1..n.
 * Graph can be directed or undirected, with multiedges and loops.
 * Graph can have cyclef of negative weight.
 * d[v] - distance to v from v0.
 * p[v] - previous vertex in a shortest path to v from v0.
 * mark[v] - v is reachable from a negative cycle.
 * Complexity: time -> O(nm).
*/

struct Edge{
    int v, u, w;
};
int n,m; cin >> n >> m;
vector<Edge> edge(m);    
for(int i=0; i<m; ++i){
    int v,u,w; cin >> v >> u >> w;
    edge[i] = {v,u,w};
}

vector<ll> d(n+1,INF_LL);
vector<int> p(n+1);
vector<bool> mark(n+1);

//detected negcycle vertices are marked
auto bellman = [&](int v0)->void{
    d[v0] = 0;
    for(int t=0; t<n; ++t){
        for(auto [v,u,w] : edge)
            if(d[v]<INF_LL && d[v]+w<d[u]){
                d[u] = max(d[v]+w, -INF_LL);
                p[u] = v;
                if(t==n-1)
                    mark[u] = true;
            }
    } 
};
bellman(v0);

for(int t=0; t<n; ++t){
    for(auto [v,u,w] : edge)
        if(mark[v])
            mark[u] = true;        
}

for(int v=1; v<=n; ++v){
    if(d[v]==INF_LL)
        // v unreachable from v0
    else if(mark[v])
        // d[v] = -INFINITY
    else
        // finite d[v]
}  

