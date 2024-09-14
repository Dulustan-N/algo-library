/**
 * DFS algorithm to find all connected components.
 * vertices: 1..n.
 * comp[i] - (i+1)-th component.
 * Complexity: time -> O(n+m). 
*/

int n, m;
vector<vector<int>> g(n+1);
vector<bool> used(n+1);

vector<vector<int>> comp;
auto dfs = [&](int v, auto&& dfs)->void{
    used[v] = true;
    comp.back().push_back(v);
    for(auto u : g[v])
        if(!used[u])        
            dfs(u, dfs);
}

for(int v=1; v<=n; ++v)
    if(!used[v]){
        comp.push_back({});
        dfs(v, dfs);
    }

