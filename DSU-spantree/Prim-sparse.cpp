/**
 * Prim's algorithm to find Minimal Spanning Tree (MST)
 * in a weighted undirected graph.
 * vertices: 1..n.
 * This should be used for SPARSE graphs (m << n^2).
 * Complexity: time -> O((m+n) log n), space -> O(m).
*/

int n,m; cin >> n >> m;
vector<vector<pair<int,int>>> g(n+1);
for(int i=0; i<m; ++i){
    int v,u,w; cin >> v >> u >> w;
    g[v].push_back({u,w});
    g[u].push_back({v,w});
}

vector<pair<int,int>> mst;
auto prim = [&](int v0)->void{
    vector<ll> d(n+1, INF_LL); 
    vector<int> p(n+1); 
    vector<bool> used(n+1);
    d[v0] = 0; 
    set<pair<int,int>> q; q.insert({d[v0],v0});    
    while(!q.empty()){
        int v = q.begin()->second;
        q.erase(q.begin());
        used[v] = true;
        mst.push_back({p[v], v});
        for(auto [u,w] : g[v])
            if(!used[u] && d[u] > w){
                q.erase({d[u],u});
                d[u] = w;
                p[u] = v;
                q.insert({d[u],u});
            }        
    }    
};
prim(1);