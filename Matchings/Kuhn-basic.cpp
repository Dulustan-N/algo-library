/**
 * Kuhn's algorithm to find maximal matching with no optimizations.
 * Given is bipartite graph with parts of sized n1 and n2, and m edges. 
 * First part: 1..n1, second part: n1+1..n1+n2. 
 * mt[v] - v (1<=v<=n1+n2) is matched to mt[v].
 * Complexity: time -> O(n1*m).
*/

vector<vector<int>> g(n1+n2+1);
vector<int> mt(n1+n2+1);
vector<bool> used(n1+1);
auto kuhn = [&](int v, auto&& kuhn)->bool{
    if(used[v]) 
        return false;
    used[v] = true;
    for(auto u : g[v])
        if(!mt[u] || kuhn(mt[u], kuhn)){
            mt[u] = v; mt[v] = u;
            return true;
        }
    return false;
};

int cnt=0;
for(int v=1; v<=n1; ++v){
    fill(used.begin(), used.end(), false);
    if(kuhn(v, kuhn))
        ++cnt;
}
