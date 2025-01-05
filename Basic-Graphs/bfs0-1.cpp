/**
 * 0-1 BFS algorithm.
 * vertices: 1..n.
 * Each edge has a weight of 0 or 1 (0-1 graph).
 * 0-1 BFS finds shortest distances in 0-1 graph.
 * Complexity: time -> O(n+m).
*/

int n, m;
vector<vector<pair<int,int>>> g(n+1);
vector<ll> d(n+1, INF_LL);

deque<int> q;
d[v0] = 0;
q.push_back(v0);       
while(q.size()){
    int v = q.front(); q.pop_front();
    for(auto [u,w] : g[v]){
        if(d[u] > d[v] + w){
            d[u] = d[v] + w;
            if(w == 1) q.push_back(u);
            else q.push_front(u);                
        }
    }
}

