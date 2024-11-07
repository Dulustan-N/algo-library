/**
 * Lowest common ancestor (LCA) by binary lifting.
 * vertices: 1..n, queries: 0..Q-1.
 * dfs - precalculates binary lifts -> O(n log n).
 * up[v][h] - (1<<h)-th ancestor of v.
 * lca(v, u) - find LCA of v and u -> O(log n).
*/

int H=__lg(n);
vector<vector<int>> up(n+1, vector<int>(H+1));
vector<int> d(n+1);
auto dfs = [&](int v, int v0, auto&& dfs)->void{
    up[v][0] = v0;
    for(int h=1; h<=H; ++h)
        up[v][h] = up[up[v][h-1]][h-1];
    for(auto u : g[v])
        if(u!=v0){     
            d[u] = d[v] + 1;       
            dfs(u,v,dfs);
        }
};
dfs(1,1,dfs);

auto lca = [&](int v, int u)->int{
    if(d[v]<d[u]) swap(v,u);
    for(int h=H; h>=0; --h)
        if(d[up[v][h]] >= d[u])
            v = up[v][h];   
    if(v==u) return v;
    for(int h=H; h>=0; --h)
        if(up[v][h] != up[u][h]){
            v = up[v][h];
            u = up[u][h];
        }
    return up[v][0];
};

//find distance between v and u
auto dist = [&](int v, int u)->int{
    int l = lca(v, u);
    return d[v] + d[u] - 2 * d[l];        
};