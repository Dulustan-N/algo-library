/**
 * Lowest common ancestor (LCA) by binary lifting.
 * Also calculates minimal weight on path between nodes.
 * vertices: 1..n, queries: 0..Q-1.
 * dfs - precalculates binary lifts -> O(n log n).
 * up[v][h] - (1<<h)-th ancestor of v.
 * upmin[v][h] - minimal weight on path from v to (1<<h)-th ancestor of v.
 * get(v, u) - get min weight of an edge on path between v and u -> O(log n).
*/

vector<vector<pair<int,int>>> g(n+1);

int H = __lg(n);
vector<vector<int>> up(n+1, vector<int>(H+1));
vector<vector<int>> upmin(n+1, vector<int>(H+1));
vector<int> d(n+1);
auto dfs = [&](int v, int v0, int w0, auto&& dfs)->void{
    up[v][0] = v0;
    upmin[v][0] = w0;
    for(int h=1; h<=H; ++h){
        up[v][h] = up[up[v][h-1]][h-1];
        upmin[v][h] = min(upmin[v][h-1], upmin[up[v][h-1]][h-1]);
    }
    for(auto [u,w] : g[v])
        if(u!=v0){     
            d[u] = d[v] + 1;       
            dfs(u,v,w,dfs);
        }
};
dfs(1,1,0,dfs);

auto get = [&](int v, int u){
    int res = INF;
    if(d[v] < d[u]) swap(v, u);
    for(int h=H; h>=0; --h)
        if(d[up[v][h]] >= d[u]){
            res = min(res, upmin[v][h]);
            v = up[v][h];
        }
    if(v == y) return res;    
    for(int h=H; h>=0; --h)
        if(up[v][h] != up[y][h]){
            res = min(res, upmin[v][h]);
            res = min(res, upmin[u][h]);
            v = up[v][h];
            u = up[u][h];
        }
    res = min(res, min(upmin[v][0], upmin[u][0]));
    return res;
};
