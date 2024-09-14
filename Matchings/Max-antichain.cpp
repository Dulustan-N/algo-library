/**
 * Problem: DAG G is given. Find a maximal antichain of G.
 * Antichain - set of vertices such that no two vertices are connected with path.
 * Dilworth's theorem: |max antichain| = |min path cover of transitive closure G' of G|.
 * Finding max antichain: build min path cover of G' => find min vertex cover of G' 
 *      => max antichain = all vertices not in vertex cover (so, v in L+ and v+n in R-).
 */

// Build transitive closure G' of G
for(int k=1; k<=n; ++k){
    for(int v=1; v<=n; ++v){
        for(int u=1; u<=n; ++u){
            if(g[v][k] && g[k][u])
                g[v][u] = 1;            
        }
    }
}

// Find min path cover of G'
vector<vector<int>> g(n+1);
for(int v=1; v<=n; ++v)
    for(int u=1; u<=n; ++u)
        if(g[v][u])
            h[v].push_back(u+n);

vector<int> mt(2*n+1), used(n+1);
auto kuhn = [&](int v, int i, auto&& kuhn)->bool{
    if(used[v]==i) 
        return false;
    used[v] = i;
    for(auto u : h[v])
        if(!mt[u]){
            mt[u] = v; mt[v] = u; 
            return true;
        }
    for(auto u : h[v])
        if(kuhn(mt[u], i, kuhn)){
            mt[u] = v; mt[v] = u;
            return true;
        }
    return false;
};

vector<int> mt(2*n+1), used(n+1);
int cnt=0;
for(int v=1; v<=n; ++v){
    if(kuhn(v, v, kuhn))
        ++cnt;
}
// find minimal vertex cover of G'
used.assign(2*n+1, 0);
auto dfs = [&](int v, auto&& dfs)->void{
    if(used[v]) return;
    used[v] = 1;
    for(auto u : g[v])
        if(u != mt[v]){
            used[u] = 1;
            dfs(mt[u], dfs);
        }
};
for(int v=1; v<=n; ++v){
    if(!mt[v])
        dfs(v, dfs);
}

// add all vertices not in matching, to antichain
vector<int> antichain;
for(int v=1; v<=n; ++v){
    if(!used[v] || used[v+n])
        continue;
    antichain.push_back(v);
}