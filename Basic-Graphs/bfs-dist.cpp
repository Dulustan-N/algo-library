/**
 * BFS algorithm to find shortest distances.
 * vertices: 1..n.
 * d[v] - distance to v.
 * p[v] - previous vertex on shortest path.
 * Complexity: time -> O(n+m).
*/ 

int n, m;
vector<vector<int>> g(n+1);

vector<ll> d(n+1);
vector<int> p(n+1);
deque<int> q;
d[v0] = 0;
q.push_back(v0);       
while(q.size()){
    int v = q.front(); q.pop_front();
    for(auto u : g[v]){
        if(d[u]==-1){
            d[u] = d[v] + 1;
            p[u] = v;
            q.push_back(u);                
        }
    }
}


