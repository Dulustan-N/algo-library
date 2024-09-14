/**
 * Dinic's algorithm to find max flow.
 * vertices: 1..n, edges: 0..m-1.
 * g[v][t] - number of edge adjacent to v.
 * Edge: to - vertex to which edge flows, f - the flow of the edge,
 *       c - capacity of the edge.
 * dinic(s, t, scale) - calculate value of max flow from s to t, 
 *                  using only flows of size >= scale.
 * Complexity: time -> O(n^2 m).
 */

struct Edge{
    int to;
    ll f, c;
};
vector<vector<int>> g(n+1);
vector<Edge> edge;
for(int i=0; i<m; ++i){
    int v,u,c; cin >> v >> u >> c;
    g[v].push_back(edge.size());
    edge.push_back({u,0,c});
    g[u].push_back(edge.size());
    edge.push_back({v,0,0}); //c for undirected edge.
}

auto dinic = [&](int s, int t, ll scale=1)->ll{
    ll maxf = 0;
    while(true){
        vector<int> d(n+1,-1);
        deque<int> q; q.push_back(s);
        d[s] = 0;
        while(q.size()){
            auto v = q.front(); q.pop_front();
            for(auto i : g[v]){
                auto [u,f,c] = edge[i];
                if(d[u] != -1 || c-f < scale) continue;
                d[u] = d[v] + 1;
                q.push_back(u);                    
            }
        }
        if(d[t] == -1) break;
        vector<int> ptr(n+1);
        auto dfs = [&](int v, ll push, auto&& dfs)->ll{
            if(v == t) return push;
            for(; ptr[v]<g[v].size(); ++ptr[v]){
                int i = g[v][ptr[v]];
                auto &[u,f,c] = edge[i];
                if(d[u] != d[v]+1 || c-f < scale) continue;
                auto x = dfs(u, min(push, c-f), dfs);
                if(x){
                    f += x;
                    edge[i^1].f -= x;
                    return x;
                }                    
            } 
            return 0;
        };            
        ll newf = 0;
        while(newf = dfs(s, INF_LL, dfs))
            maxf += newf;        
    }
    return maxf;
};  

//scaling
ll maxf = 0;
for(int h=29; h>=0; --h)
    maxf += dinic(1, n, 1ll<<h);    
