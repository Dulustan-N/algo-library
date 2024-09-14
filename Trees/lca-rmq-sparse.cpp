/**
 * Lowest common ancestor (LCA) by RMQ.
 * vertices: 1..n, queries: 0..Q-1.
 * Sparse sp - sparse table for the RMQ.
 * dfs - makes euler array of the tree.
 * euler - euler array of the tree.
 * euler[i] - pair {d[v], v}.
 * tin[v] - index of first appearance of v in euler array.
 * d[v] - distance to v from root.
 * up[v][h] - (1<<h)-th ancestor of v.
 * lca(v, u) - find LCA of v and u.
 * Complexity: precompute -> O(n log n), LCA query -> O(1).
*/

struct Sparse{
    vector<vector<pair<int,int>>> t;
    Sparse(vector<pair<int,int>> &a){
        int n = a.size(), H = __lg(n);
        t.resize(H+1,vector<pair<int,int>>(n));
        for(int i=0; i<n; ++i)
            t[0][i] = a[i];
        for(int h=1; h<=H; ++h)
            for(int i=0; i+(1<<h)<=n; ++i)
                t[h][i] = min(t[h-1][i], t[h-1][i+(1<<(h-1))]); 
    }
    pair<int,int> get(int l, int r){
        if(l>r) swap(l,r);
        ++r;
        int h = __lg(r-l);
        return min(t[h][l], t[h][r-(1<<h)]);
    }
};


vector<int> d(n+1), tin(n+1);
vector<pair<int,int>> euler;
auto dfs = [&](int v, int v0, auto&& dfs)->void{
    tin[v] = euler.size();
    euler.push_back({d[v],v});
    for(auto u : g[v]){
        if(u==v0) continue;
        d[u] = d[v] + 1;
        dfs(u,v,dfs);
        euler.push_back({d[v],v});
    }
};

dfs(1,0,dfs);
Sparse sp(euler);
auto lca = [&](int v, int u)->int{
    return sp.get(tin[v], tin[u]).second;
};
