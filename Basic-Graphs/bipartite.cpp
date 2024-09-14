/**
 * DFS algorithm to check if graph is bipartite.
 * vertices: 1..n.
 * Complexity: time -> O(n+m).
*/

int n, m;
vector<vector<int>> g(n+1);
vector<int> color(n+1);

auto dfs = [&](int v, auto&& dfs)->bool{
    for(auto u : g[v]){
        if(color[u]==0){
            color[u] = 3-color[v];
            if(!dfs(u,dfs)) return false;
        }
        else if(color[u] == color[v])
            return false;
    }
    return true;
};

for(int v=1; v<=n; ++v){
    if(color[v]==0){
        color[v] = 1;
        if(!dfs(v, dfs)) 
            //not bipartite.          
    }   
}
   
