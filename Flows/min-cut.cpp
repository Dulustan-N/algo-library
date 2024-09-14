/**
 * Minimum cut (S,T) of a network, where s in S, t in T.
 * Run dfs after finding max_flow s -> t.
 * mincut = S.
 */

vector<bool> used(n+1);
auto dfs = [&](int v, auto&& dfs)->void{
    used[v] = true;
    for(auto i : g[v]){
        auto [u,f,c] = edge[i];
        if(used[u] || c-f==0) continue;
        dfs(u, dfs);
    }
};
dfs(1, dfs);

vector<int> mincut;
for(int v=1; v<=n; ++v){
    if(!used[v]) continue;
    for(auto i : g[v]){
        if(!used[edge[i].to])
            mincut.push_back(i/2);
    }
}