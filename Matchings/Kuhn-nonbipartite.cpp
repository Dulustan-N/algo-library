/**
 * Euristic Kuhn's algorithm's modifiction
 * to find maximal matching in non-bipartite graphs.
 * vertices: 1..n.
 * mt[v] - v is matched to mt[v].
 * ITER - fixed number of iterationsm, can be tweaked or replaced by time measurement.
 * Complexity: time -> supposedly fast enough.
*/

mt19937 rng(time(0));
vector<vector<int>> g(n+1);
vector<int> mt(n+1), used(n+1);

auto kuhn = [&](int v, int i, auto&& kuhn)->bool{
    if(used[v]==i)
        return false;
    used[v] = i;
    shuffle(g[v].begin(), g[v].end(), rng);      
    for(auto u : g[v])
        if(!mt[u]){
            mt[u] = v; mt[v] = u; 
            return true;
        }
    for(auto u : g[v]){
        if(used[mt[u]]==i) continue;
        int x = mt[u], y = mt[v];
        mt[u] = v; mt[v] = u;
        if(kuhn(x, i, kuhn))
            return true;
        mt[u] = x; mt[v] = y;
    }
    return false;
};

int cnt=0;
int ITER = 10;
while(ITER--){
    used.assign(n+1, 0);
    for(int v=1; v<=n; ++v){
        if(!mt[v] && kuhn(v, v, kuhn))
            ++cnt;
    }
}
