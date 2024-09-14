/**
 * Problem: DAG G is given. Find size of minimal path cover of G.
 * vertices: 1..n
 * Solution: Duplicate each vertex v into v+n to make new graph H (no edges yet);
 * for each edge v -> u in G make edge v -> u+n in H; 
 * define H' as graph H + edges v+n -> v for all v.
 * Path in G = path in H'.
 * Path in H' <-> matching in H (1..n is first part, n+1..2*n is second).
 * Minimal path cover of G <-> non-intersecting matchings in maximal matching.
 * |Min path cover| = n - |max matching|.
 */

// build H
vector<vector<int>> g(n+1);
vector<vector<int>> h(n+1);
for(int v=1; v<=n; ++v)
    for(int u=1; u<=n; ++u)
        if(g[v][u])
            h[v].push_back(u+n);

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

// find maximal matching in H
vector<int> mt(2*n+1), used(n+1);
int cnt=0;
for(int v=1; v<=n; ++v){
    if(kuhn(v, v, kuhn))
        ++cnt;
}

int ans = n - cnt;