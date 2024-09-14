/**
 * Kuhn's algorithm to find maximal matching with simple but efficient optimizations.
 * Given is bipartite graph with parts of sized n1 and n2, and m edges.
 * First part: 1..n1, second part: n1+1..n1+n2. 
 * mt[v] - v (1<=v<=n1+n2) is matched to mt[v].
 * Optimization 1: no zeroing used array.
 * Optimization 2: greedy matching comes first in kuhn.
 * Optimization 3 (optional): random shuffling to beat antikuhn tests.
 * Complexity: time -> O(n1*m).
*/

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<vector<int>> g(n1+n2+1);
vector<int> mt(n1+n2+1);
vector<int> used(n1+1);

auto kuhn = [&](int v, int i, auto&& kuhn)->bool{
    if(used[v]==i) 
        return false;
    used[v] = i;
    for(auto u : g[v])
        if(!mt[u]){
            mt[u] = v; mt[v] = u;
            return true;
        }
    for(auto u : g[v])
        if(kuhn(mt[u], i, kuhn)){
            mt[u] = v; mt[v] = u;
            return true;
        }
    return false;
};

int cnt=0;
for(int v=1; v<=n1; ++v){
    // shuffle(g[v].begin(), g[v].end(), rng);
    if(kuhn(v, v, kuhn))
        ++cnt;
}
