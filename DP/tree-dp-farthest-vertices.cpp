/**
 * O(n) DFS-DP algorithm to find farthest vertex for each vertex in a tree. 
 * 1-based indexation for vertices.
 * It makes v=1 root of the tree.
 * dp[v] - distance to farthest vertex from v.
*/

vector<int> dp(n+1), p(n+1), h(n+1);
auto dfs0 = [&](int v, int v0, auto&& dfs0)->void{      
    for(auto u : g[v]){
        if(u==v0) continue;
        dfs0(u, v, dfs0);
        if(dp[u]+1 > dp[v]){
            h[v] = dp[v];
            dp[v] = dp[u]+1;
            p[v] = u;
        }
        else if(dp[u]+1 > h[v])
            h[v] = dp[u]+1;
    }
};
dfs0(1, 0, dfs0);

auto dfs1 = [&](int v, int v0, int up, auto &&dfs1)->void{        
    for(auto u : g[v]){
        if(u == v0) continue;            
        int down = 1+up;
        if(u == p[v]) down = max(down, 1+h[v]);
        else down = max(down, 1+dp[v]);
        dfs1(u, v, down, dfs1);
    }
    dp[v] = max(dp[v], up);
};
dfs1(1, 0, 0, dfs1);
