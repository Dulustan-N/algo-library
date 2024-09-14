/**
 * Simple DFS to find all centroids (one or two) of a tree.
 * vertices: 1..n.
 * Complexity: time -> O(n+m).
*/

auto dfs_sz = [](int v, int v0, const vector<vector<int>> &g, vector<int> &s, auto&& dfs_sz)->void{
    s[v] = 1;
    for(auto u : g[v]){
        if(u==v0) continue;
        dfs_sz(u, v, g, s, dfs_sz);
        s[v] += s[u];
    }
};
auto cen = [n](int v, int v0, const vector<vector<int>> &g, const vector<int> &s, auto&& cen)->vector<int>{
    vector<int> cent;
    for(auto u : g[v]){
        if(u==v0) continue;
        if(s[u] > n/2)
            return cen(u, v, g, s, cen);
        else if(s[u] == n - s[u])
            cent.push_back(u);
    }
    cent.push_back(v);
    return cent;
};  