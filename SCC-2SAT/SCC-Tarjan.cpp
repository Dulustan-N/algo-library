/**
 * Tarjan algorithm to find strongly connected components (SCC).
 * vertices: 1..n.
 * gc - condensed graph.
 * Complexity: time -> O((n+m) alpha(n)).
*/

int n, m; cin >> n >> m;
vector<vector<int>> g(n+1);
for(int i=0; i<m; ++i){
    int v,u; cin >> v >> u;
    g[v].push_back(u);
}

vector<bool> used(n+1);
vector<int> num(n+1), low(n+1), ssc(n+1);
stack<int> st;
int timer = 0, cnt = 0;

auto dfs = [&](int v, auto&& dfs)->void{
    num[v] = low[v] = ++timer;
    used[v] = true;
    st.push(v);
    for(auto u : g[v]){
        if(!used[u]){
            dfs(u, dfs);
            low[v] = min(low[v], low[u]);
        }
        else if(!ssc[u]){
            low[v] = min(low[v], num[u]);
        }
    }
    if(num[v]==low[v]){
        ++cnt;
        while(st.top()!=v){
            ssc[st.top()] = cnt;
            st.pop();
        }
        ssc[st.top()] = cnt;
        st.pop();
    }
};

for(int v=1; v<=n; ++v){
    if(!used[v])
        dfs(v, dfs);
}

//Graph Condensation
vector<vector<int>> gc(cnt+1);
vector<int> vis(cnt+1);
for(int v=1; v<=n; ++v){
    for(auto u : g[v])
        if(scc[u]!=scc[v] && vis[scc[u]]!=scc[v]){
            gc[scc[v]].push_back(scc[u]);
            vis[scc[u]] = scc[v];
        }
} 




