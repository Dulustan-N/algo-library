/**
 * Hopcroft-Karp algorithm to find maximal matching.
 * Given is bipartite graph with parts of sized n1 and n2, and m edges.
 * First part: 1..n1, second part: n1+1..n1+n2. 
 * mt[v] - v (1<=v<=n1+n2) is matched to mt[v].
 * Complexity: time -> O(sqrt(n) * m).
*/

vector<vector<int>> g(n1+n2+1);
vector<int> mt(n1+n2+1);
int cnt=0;
while(true){
    vector<int> d(n1+1,-1);
    deque<int> q;
    for(int v=1; v<=n1; ++v)
        if(!mt[v]){
            d[v] = 0;
            q.push_back(v);
    
        }
    bool found = false;
    while(q.size()){
        int v = q.front(); q.pop_front();
        for(auto u : g[v]){
            if(!mt[u]) found = true;
            else if(d[mt[u]]==-1){
                d[mt[u]] = d[v] + 1;
                q.push_back(mt[u]);
            }
        }
    }
    if(!found) break;

    vector<int> ptr(n1+1);
    auto dfs = [&](int v, auto&& dfs)->bool{
        for(int &i=ptr[v]; i<g[v].size(); ++i){
            int u = g[v][i];
            if(!mt[u] || d[mt[u]]==d[v]+1 && dfs(mt[u], dfs)){
                mt[v] = u; mt[u] = v;        
                return true;
            }
        }
        d[v] = -1;
        return false;
    };

    for(int v=1; v<=n1; ++v){
        if(!mt[v] && dfs(v, dfs))
            ++cnt;                       
    }
}



