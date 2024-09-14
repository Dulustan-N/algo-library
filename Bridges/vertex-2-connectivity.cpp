/**
 * Algorithm to find all vertex-2-connectivity components.
 * vertices: 1..n, edges: 0..m-1.
 * comp[e] --- number of e's component.
 * Complexity: time -> O(n+m).
*/

int n, m; cin >> n >> m;
vector<vector<pair<int,int>>> g(n+1);
for(int e=0; e<m; ++e){
    int v,u; cin >> v >> u;
    g[v].push_back({u,e});
    g[u].push_back({v,e});
}

vector<int> up(n+1), d(n+1);
vector<int> used(n+1), comp(m), st;

int cnt=0;
auto dfs = [&](int v, int e0, auto&& dfs)->void{    
    used[v] = 1; up[v] = d[v];
    for(auto [u,e] : g[v]){
        if(e==e0 || used[u]==2) continue;
        st.push_back(e);
        if(used[u]==1)
            up[v] = min(up[v], d[u]);
        else{
            d[u] = d[v] + 1;            
            dfs(u,e);
            up[v] = min(up[v], up[u]);
            if(up[u]>=d[v] && d[v]>0){
                ++cnt;
                while(st.back() != e){                    
                    comp[st.back()] = cnt;
                    st.pop_back();
                }
                comp[st.back()] = cnt;
                st.pop_back();
            }
        }
        if(d[v]==0 && st.size()){
            ++cnt;
            while(st.size()){
                comp[st.back()] = cnt;
                st.pop_back();
            }
        }
    }
    used[v] = 2;
}

for(int v=1; v<=n; ++v)
    if(!used[v])
        dfs(v, -1, dfs);

