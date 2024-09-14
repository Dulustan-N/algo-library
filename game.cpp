/**
 * General DFS to solve games on graphs.
 * vertices (states): 1..n, 
 * win[v] = 1 is winning state,
 * win[v] = -1 is losing state,
 * win[v] = 0 is unmarked (draw) state.
 * Complexity: time -> O(n+m).
 */

vector<vector<int>> g(n+1);
vector<int> win(n+1), deg(n+1);

auto dfs = [&](int v, auto&& dfs)->void{
    for(auto u : g[v]){
        if(win[u]) continue;
        --deg[u]; 
        if(win[v] == -1)
            win[u] = 1;        
        else if(deg[u] == 0){	
            win[u] = -1;
            dfs(u, dfs);
        }        
    }
} 