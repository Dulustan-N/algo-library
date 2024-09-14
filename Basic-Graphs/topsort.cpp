/**
 * O(n+m) DFS algorithm to find topological sorting in a DAG.
 * vertices: 1..n. 
 * Complexity: time -> O(n+m).
*/

int n, m; 
vector<vector<int>> g(n+1); 

vector<int> tsort, used(n+1);
auto dfs = [&](int v, auto&& dfs)->void{
    used[v] = 1;
    for(auto u : g[v]){
        if(!used[u])
            dfs(u, dfs);
    }               
    tsort.push_back(v);
};

for(int v=1; v<=n; ++v)
    if(!used[v])
        dfs(v, dfs);
reverse(tsort.begin(), tsort.end());




/**
 * O(n+m) DFS algorithm to find topological sorting in 
 * a directed graph or determine that it is cyclic.
 * 1-based indexation for vertices.
*/
int n, m; 
vector<vector<int>> g(n+1); 

vector<int> tsort, used(n+1);
auto dfs = [&](int v, auto&& dfs)->bool{
    used[v] = 1;
    for(auto u : g[v]){
        if(!used[u] && !dfs(u, dfs))
                return false;            
        else if(used[u]==1)
            return false;
    }               
    tsort.push_back(v);
    used[v] = 2;
    return true;
};

for(int v=1; v<=n; ++v)
    if(!used[v] && !dfs(v, dfs)){
        // Cycle found, so no topsort.
        return;
    }            
reverse(tsort.begin(), tsort.end());
