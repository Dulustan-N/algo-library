/**
 * DFS algorithm to find diameter of a tree.
 * vertices: 1..n. 
 * d[v] - distance to v from the DFS root.
 * far - vertex with max d[v] after DFS.
 * Complexity: time -> O(n+m).
*/

int n; 
vector<vector<int>> g(n+1); 

vector<int> d(n+1);
int far = 1;
auto dfs = [&](int v, int v0, auto&& dfs)->void{        
    if(d[v] > d[far])
        far = v;
    for(auto u : g[v]){
        if(u==v0) continue;
        d[u] = d[v] + 1;
        dfs(u,v,dfs);
    }
};
dfs(1, 0, dfs);
d[far] = 0;
dfs(far, 0, dfs);
int diam = d[far];
