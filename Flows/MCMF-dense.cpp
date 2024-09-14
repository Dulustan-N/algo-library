/**
 * Min Cost Max Flow - Johnson's algorithm.
 * vertices: 1..n, edges: 0..m-1.
 * Edge: fro - vertex from which edge flow, to - vertex to which edge flows, 
 *       cap - capacity of the edge, flow - the flow of the edge, 
 *       cost - cost of the edge.
 * Complexity: time -> O(F n^2), where F - value of MCMF.
 */

struct MCMF{
    struct Edge{
        int fro, to;
        ll cap, flow, cost;
    };
    int n;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<ll> dist, pot, push;
    vector<bool> used;
    vector<int> par;
    MCMF(int n) : n(n), g(n+1), dist(n+1), pot(n+1), push(n+1), used(n+1), par(n+1){}

    void add_edge(int v, int u, ll cap, ll cost){
        int k = e.size();
        e.push_back({v, u, cap, 0, cost});
        e.push_back({u, v, 0, 0, -cost});
        g[v].push_back(k);
        g[u].push_back(k^1);
    }
    void bellman(int s){
        fill(pot.begin(), pot.end(), INF_LL);
        pot[s] = 0;
        for(int t=0; t<n-1; ++t){
            for(auto [v,u,cap,flow,w] : e)
                if(pot[v]<INF_LL && pot[v]+w<pot[u]){
                    pot[u] = pot[v]+w;
                    pot[u] = v;
                }
        } 
    }
    pair<ll,ll> mcmf(int s, int t){
        ll flow = 0, cost = 0;
        while(true){
            fill(dist.begin(), dist.end(), INF_LL);
            fill(used.begin(), used.end(), false);
            dist[s] = 0;
            push[s] = INF_LL;            
            while(true){
                int x = -1; ll d = INF_LL;
                for(int v=1; v<=n; ++v){
                    if(!used[v] && dist[v]<d){
                        x = v;
                        d = dist[x];
                    }
                }
                if(x == -1) break;
                used[x] = true;
                for(int i : g[x]){
                    auto d2 = d + e[i].cost + pot[x] - pot[e[i].to];
                    if(!used[e[i].to] && e[i].flow < e[i].cap && d2 < dist[e[i].to]){
                        dist[e[i].to] = d2;
                        push[e[i].to] = min(push[x], e[i].cap - e[i].flow);
                        par[e[i].to] = i;
                    }
                }
            }            
            if(!used[t]) break;
            for(int v=1; v<=n; ++v){
                dist[v] += pot[v] - pot[s];
            }        
            cost += dist[t] * push[t];
            flow += push[t];
            int x = t;
            while(x != s){
                e[par[x]].flow += push[t];
                e[par[x]^1].flow -= push[t];
                x = e[par[x]^1].to;
            }
            dist.swap(pot);
        }
        return {flow, cost};
    }
};