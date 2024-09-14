/**
 * O(m) Hierholzer’s algorithm to find eulerian cycle.
 * vertices: 1..n.
 * Graph can be directed or undirected, with multiedges and loops.
 * If graph is eulerian, this finds eulerian cycle.
 * This can be easily adapted to find eulerian path in semieulerian graph.
 * This implementation uses "pointers" to mark "deleted" edges.
 * Complexity: time -> O(n+m).
*/

int n,m; cin >> n >> m;
vector<vector<pair<int,int>>> g(n+1);    
for(int e=0; e<m; ++e){
    int v,u; cin >> v >> u;
    g[v].push_back({u,e});
    g[u].push_back({v,e}); //if undirected graph
}

vector<bool> used(m);
vector<int> first(n+1);
vector<pair<int,int>> path;

auto euler = [&](int v, auto&& euler)->void{    
    while(first[v] < g[v].size()){
        auto [u,i] = g[v][first[v]];
        ++first[v];
        if(!used[i]){
            used[i] = true;
            euler(u, euler);               
            path.push_back({v,u});                     
        }
    }
};

euler(1, euler);  

if(path.size() < m){
    // something is wrong.
    return;
} 