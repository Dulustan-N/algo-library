/**
 * 2SAT problem solution with Kosaraju.
 * vertices: 1..n.
 * gt - transposed graph to g.
 * v - true condition, v+n - false condition.
 * yes[v] = true if we v = true in 2SAT.
 * Complexity: time -> O(n+m).
*/

int n, m; 
vector<vector<int>> g(2*n+1), gt(2*n+1);
auto neg = [n](int v)->int{
    if(v<=n) return v+n;
    else return v-n;
};

for(int i=0; i<m; ++i){
    ...        
    g[neg(v)].push_back(u);
    g[neg(u)].push_back(v);
    gt[u].push_back(neg(v));
    gt[v].push_back(neg(u));
}

// Topsort
vector<bool> used(2*n+1);
vector<int> tsort;
auto dfs0 = [&](int v, auto&& dfs0)->void{
    used[v] = true;
    for(auto u : g[v]){
        if(!used[u])
            dfs0(u, dfs0);
    }               
    tsort.push_back(v);
};
for(int v=1; v<=2*n; ++v)
    if(!used[v])
        dfs0(v, dfs0);
reverse(tsort.begin(), tsort.end());

// Kosaraju
vector<int> scc(2*n+1);
int cnt=0;
auto dfs1 = [&](int v, auto&& dfs1)->void{
    scc[v] = cnt;
    for(auto u : gt[v])
        if(!scc[u])
            dfs1(u, dfs1);
};
for(auto v : tsort)
    if(!scc[v]){
        ++cnt;
        dfs1(v, dfs1);
    }

vector<bool> yes(n+1);
for(int v=1; v<=n; ++v){
    if(scc[v] > scc[v+n])
        yes[v] = true;
    else if(scc[v] == scc[v+n]){
        // no solution.
        return;
    }        
}

