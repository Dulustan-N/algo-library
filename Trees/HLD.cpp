/**
 * Heavy-Light Decomposition (HLD) of a tree.
 * vertices: 1..n.
 * dfs_sz(v, v0) - calculates size of subtree of v and places 
 * its largest child (by subtree size) in the front. 
 * s[v] - size of v's subtree.
 * p[v] - v's parent in a tree.
 * d[v] - v's distance from the root.
 * head[v] - head of a heavy path containing v.
 * tr - segment tree built over HLD.
 * hld(v0) - builds HLD with root at v0.
 * path(v, u) - range query over path v->u.
 * Complexity: time -> O(n log n).
*/

vector<int> s(n+1);
auto dfs_sz = [&](int v, int v0, auto&& dfs_sz)->void{
    s[v] = 1;
    for(auto &u : g[v])
        if(u==v0){
            swap(u, g[v].back());
            g[v].pop_back();
            break;
        }
    for(auto &u : g[v]){
        dfs_sz(u, v, dfs_sz);
        if(s[g[v][0]] < s[u])
            swap(g[v][0], u);
        s[v] += s[u];
    }
};
//Build HLD
vector<int> tin(n+1), d(n+1), p(n+1), head(n+1);
int timer = 0;
auto hld = [&](int v, auto&& hld)->void{
    tin[v] = timer++;
    for(auto u : g[v]){
        head[u] = (u==g[v][0] ? head[v] : u);
        p[u] = v;
        d[u] = d[v] + 1;
        hld(u, hld);
    }
};
head[1] = 1;
dfs_sz(1, 0, dfs_sz);
hld(1, hld);

//Build Segment tree over HLD
SegTree tr(n);
for(int v=1; v<=n; ++v)
    tr.upd(tin[v], a[v]);

//Query over path in graph
auto path = [&](int v, int u)->ll{
    int res = -INF;
    while(head[v] != head[u]){
        if(d[head[v]] < d[head[u]]) swap(v, u);
        res = max(res, tr.get(tin[head[v]], tin[v]+1));
        v = p[head[v]];            
    }
    if(d[v] < d[u]) swap(v, u);
    res = max(res, tr.get(tin[u], tin[v]+1));
    return res;
};    
