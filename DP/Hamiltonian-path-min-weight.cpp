/**
 * Problem: in a weighted graph, find hamiltonian path of min weight.
 * 0-based indexing for vertices.
 * w[i][j] - weight of edge i->j.
 * dp[mask][i] - min weigth hamiltonian path in a subgraph of mask that ends in vertex i.
 * p[mask][i] - previous vertex to i in path dp[mask][i].
 * Complexity: time -> O(2^n n^2), space -> O(2^n n).
*/

// No answer recovery
vector<vector<ll>> dp((1<<n),vector<ll>(n, INF_LL));
for(int i=0; i<n; ++i)
    dp[(1<<i)][i] = 0;
for(int mask=1; mask<(1<<n); ++mask){
    for(int i=0; i<n; ++i){
        if(dp[mask][i]==INF) continue;
        for(int j=0; j<n; ++j){
            if((mask>>j)&1 || w[i][j]==-1) continue;
            int mask1 = mask | (1<<j);
            dp[mask1][j] = min(dp[mask1][j], dp[mask][i] + w[i][j]);
        }            
    }
}
ll ans = INF_LL;
for(int i=0; i<n; ++i)
    ans = min(ans, dp[(1<<n)-1][i]);


// With answer recovery
vector<vector<int>> dp((1<<n),vector<int>(n, INF));
vector<vector<int>> p((1<<n),vector<int>(n, -1));
for(int i=0; i<n; ++i)
    dp[(1<<i)][i] = 0;
for(int mask=1; mask<(1<<n); ++mask){
    for(int i=0; i<n; ++i){
        if(dp[mask][i]==INF) continue;
        for(int j=0; j<n; ++j){
            if((mask>>j)&1 || w[i][j]==-1) continue;
            int mask1 = mask | (1<<j);
            if(dp[mask1][j] > dp[mask][i] + w[i][j]){
                dp[mask1][j] = dp[mask][i] + w[i][j];
                p[mask1][j] = i;
            }
        }            
    }
}

int mask = (1<<n)-1, i = 0;
for(int j=0; j<n; ++j)
    if(dp[mask][j] < dp[mask][i])
        i = j;
cout << dp[mask][i] << endl;
vector<int> path;
while(i!=-1){
    path.push_back(i+1);
    int mask1 = mask ^ (1<<i);
    i = p[mask][i];        
    mask = mask1;
}
reverse(path.begin(), path.end());


// with adjacency lists representation of graph.
vector<vector<ll>> dp((1<<n),vector<ll>(n, INF_LL));
for(int i=0; i<n; ++i)
    dp[(1<<i)][i] = 0;
for(int mask=1; mask<(1<<n); ++mask){
    for(int i=0; i<n; ++i){
        if(dp[mask][i]==INF) continue;
        for(auto [j,w] : g[i]){
            if((mask>>j)&1) continue;
            int mask1 = mask | (1<<j);
            dp[mask1][j] = min(dp[mask1][j], dp[mask][i] + w);
        }            
    }
}
