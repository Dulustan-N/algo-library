/**
 * Edmonds-Karp's algorithm to find max flow.
 * vertices: 1..n, edges: 0..m-1.
 * g[v][t] - number of edge adjacent to v.
 * Edge: to - vertex to which edge flows, f - the flow of the edge,
 *       c - capacity of the edge.
 * karp(s, t, scale) - calculate value of max flow from s to t, 
 *                  using only flows of size >= scale.
 * Complexity: time -> min(O(nm^2), O(mF)), where F - value of max flow.
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

auto karp = [&](int s, int t, ll scale=1)->ll{
    ll maxf=0;
    while(true){
        vector<int> p(n+1);
        vector<ll> push(n+1);
        push[s] = INF_LL;
        deque<int> q; q.push_back(s);
        while(q.size()){
            auto v = q.front(); q.pop_front();
            if(v == t) break;
            for(auto i : g[v]){
                auto [u,f,c] = edge[i];
                if(p[u] || c-f < scale) continue;
                p[u] = i^1;
                push[u] = min(push[v], c-f);
                q.push_back(u);
                if(u == t){q.clear(); break;}  
            }
        }
        ll newf = push[t];
        if(!newf) break;
        for(int v=t; v!=s; v=edge[p[v]].to){
            edge[p[v]^1].f += newf;
            edge[p[v]].f -= newf;
        }
        maxf += newf;
    }
    return maxf;        
};

//scaling
ll maxf = 0;
for(int h=29; h>=0; --h)
    maxf += karp(1, n, 1ll<<h);    