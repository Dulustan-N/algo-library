/**
 * O(n+m) DFS algorithm to find any cycle.
 * vertices: 1..n.
 * Graph can be directed or undirected.
 * Graph can have loops and multiedges.
 * Complexity: time -> O(n+m).
*/

//find cycle of size >=2 in directed graph
int n, m; 
vector<vector<int>> g(n+1); 
vector<int> p(n+1), used(n+1);

int start = 0, fin = 0;
auto dfs = [&](int v, auto&& dfs)->bool{
    used[v] = 1;
    for(auto u : g[v]){
        if(used[u]==0){
            p[u] = v;
            if(dfs(u, dfs)) return true;
        }
        else if(used[u]==1){
            fin = v;
            start = u;
            return true; 
        }
    }               
    used[v] = 2;
    return false;
};

for(int v=1; v<=n; ++v){
    if(used[v]==0 && dfs(v, dfs))            
        break;
}

if(start==0){
    // No cycles 
    return;
}
vector<int> cycle;
int v = fin; 
cycle.push_back(v);
while(v != start){
    v = p[v];
    ans.push_back(v);
}
reverse(cycle.begin(), cycle.end());
cycle.push_back(start);
// cycle - one found cycle