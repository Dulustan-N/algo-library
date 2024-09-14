/**
 * Level Ancestor (LA) by binary lifting.
 * vertices: 1..n, queries: 0..Q-1.
 * dfs - precalculates binary lifts -> O(n log n).
 * up[v][h] - (1<<h)-th ancestor of v.
 * la(v, k) - find k-th ancestor of v -> O(log n).
*/

int H=__lg(n);
vector<vector<int>> up(n+1, vector<int>(H+1));
auto dfs = [&](int v, int v0, auto&& dfs)->void{
    up[v][0] = v0;
    for(int h=1; h<=H; ++h)
        up[v][h] = up[up[v][h-1]][h-1];
    for(auto u : g[v])
        if(u!=v0){            
            dfs(u,v,dfs);
        }
};
dfs(1,1,dfs);

auto la = [&](int v, int k)->int{
    for(int h=H; h>=0; --h)
        if((1<<h)<=k){
            v = up[v][h];
            k -= (1<<h);
        }
    return v;
};

