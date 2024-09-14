/**
 * O(m log m) Kruskal's algorithm to find Minimal Spanning Tree (MST)
 * in a weighted undirected graph.
 * vertices: 1..n.
 * Complexity: time -> O(m log m), space -> O(m).
*/

struct DSU{
    vector<int> p, s;
    DSU(int n){
        p.resize(n+1); s.resize(n+1, 1);
        iota(p.begin(), p.end(), 0);
    }
    int get(int v){
        if(v != p[v])
            p[v] = get(p[v]);     
        return p[v];
    }
    void unite(int v, int u){
        v = get(v);
        u = get(u);
        if(v == u) return;
        if(s[v] < s [u]) swap(v,u);
        p[u] = v;
        s[v] += s[u];    
    }
    int size(int v){
        return s[get(v)];
    }
    bool same(int v, int u){
        return get(v) == get(u);
    } 
};

struct Edge{
    int v, u, w;
};
vector<Edge> edge;
int n,m; cin >> n >> m;
for(int i=0; i<m; ++i){
    int v,u,w; cin >> v >> u >> w;
    if(v > u) swap(v, u);
    edge.push_back({v,u,w});
}

DSU dsu(n);
vector<pair<int,int>> mst;
sort(edge.begin(), edge.end(), [](Edge &a, Edge &b){
    return a.w<b.w;
});

for(auto [v,u,w] : edge){
    if(!dsu.same(v,u)){
        dsu.unite(v,u);
        mst.push_back({v,u});
    }
}

