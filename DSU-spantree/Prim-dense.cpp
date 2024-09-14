/**
 * Prim's algorithm to find Minimal Spanning Tree (MST)
 * in a weighted undirected graph.
 * vertices: 1..n.
 * This should be used for DENSE graphs (m ~ n^2).
 * Complexity: time -> O(n^2+m), space -> O(m).
*/

int n, m; cin >> n >> m;
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
    for(int i=0; i<n; ++i){
        int v = 0;
        for(int u=1; u<=n; ++u)
            if(!used[u] && (!v || d[u]<d[v]))
                v = u;
        used[v] = true;
        mst.push_back({p[v], v});
        for(auto [u,w] : g[v])
            if(!used[u] && d[u] > w){
                d[u] = w;
                p[u] = v;
            }  
    }   
};

prim(1);




//Classical style Prim
int n,m; 
vector<vector<pair<int,int>>> g;
vector<pair<int,int>> mst;

void prim(int v0){
    vector<ll> d(n+1,INF_LL); vector<int> p(n+1); 
    vector<bool> used(n+1);
    d[v0] = 0;     
    ll total=0;
    for(int i=0; i<n; ++i){
        int v = 0;
        for(int u=1; u<=n; ++u)
            if(!used[u] && (!v || d[u]<d[v]))
                v = u;
        used[v] = true;
        mst.push_back({p[v], v});
        for(auto [u,w] : g[v])
            if(!used[u] && d[u] > w){
                d[u] = w;
                p[u] = v;
            }  
    }
}

void solve(){
    cin >> n >> m;
    g.resize(n+1);
    forn(tt,0,m){
        int v,u,w; cin >> v >> u >> w; v--; u--;
        g[v].push_back({u,w});
        g[u].push_back({v,w});
    }
    prim(1);   
}

