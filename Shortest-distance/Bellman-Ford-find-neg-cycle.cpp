/**
 * Bellman-Ford algorithm to find a cycle of negative weight.
 * vertices: 1..n.
 * Graph can be directed or undirected, with multiedges and loops.
 * d[v] - distance to v from v0.
 * p[v] - previous vertex in a shortest path to v from v0.
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

auto bellman_cycle = [&]()->vector<int>{
    vector<ll> d(n+1);
    vector<int> p(n+1);
    int x;
    for(int t=0; t<n; ++t){
        x=0;
        for(auto [v,u,w] : edge){
            if(d[v]<INF_LL && d[v]+w<d[u]){
                d[u] = max(d[v]+w, -INF_LL);
                p[u] = v;
                x = u;
            }
        }
    }
    if(!x) return {};   
    vector<int> cycle; 
    for(int t=0; t<n; ++t)
        x = p[x];
    cycle.push_back(x);
    for(int v=p[x]; v!=x; v=p[v])
        cycle.push_back(v);
    reverse(cycle.begin(), cycle.end());        
    return cycle;      
};    

auto cycle = bellman_cycle();


