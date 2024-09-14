/**
 * O(m) Hierholzer’s algorithm to find eulerian cycle.
 * vertices: 1..n.
 * Graph can be directed or undirected, with multiedges and loops.
 * If graph is eulerian, this finds eulerian cycle.
 * This can be easily adapted to find eulerian path in semieulerian graph.
 * This implementation uses multisets to erase edges.
 * Complexity: time -> O((n+m) log m).
*/

int n,m; cin >> n >> m;
vector<multiset<int>> g(n+1);    
for(int i=0; i<m; ++i){
    int v,u; cin >> v >> u;
    g[v].insert(u);
    g[u].insert(v); //if undirected graph
}

vector<pair<int,int>> path;
auto euler = [&](int v, auto&& euler)->void{    
    while(!g[v].empty()){
        int u = *g[v].begin();
        g[v].erase(g[v].find(u));
        g[u].erase(g[u].find(v)); //if undirected graph
        euler(u, euler);        
        path.push_back({v,u});
    }    
};
euler(1, euler); 

if(path.size() < m){
    // something is wrong.
    return;
}