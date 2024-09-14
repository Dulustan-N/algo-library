/**
 * "Chromatic number" problem: color vertices of an undirected graph
 * in a min number of colors so that each edge connects vertices of different colors.
 * 0-based indexing for vertices.
 * e[v] - mask of vertices adjacent to v.
 * dp[mask] - minimal number of colors to color subgraph of mask. 
 * Complexity: time -> O(3^n n), space -> (2^n n).
*/

int n, m; cin >> n >> m;
vector<int> e(n);
for(int i=0; i<m; ++i){
    int v,u; cin >> v >> u; --v;--u;
    e[v] |= (1<<u);
    e[u] |= (1<<v);
}

vector<int> dp(1<<n, INF), p(1<<n, -1);    
for(int mask=1; mask<(1<<n); ++mask){
    int res=0;
    for(int i=0; i<n; ++i){
        if(!((mask>>i)&1)) continue;
        res |= e[i];
    }
    if(!(res&mask)){
        dp[mask] = 1;   
        p[mask] = mask;
    }
}

for(int mask=1; mask<(1<<n); ++mask){
    for(int subm=mask; subm>0; subm = (subm-1)&mask){
        if(dp[subm]==1 && dp[mask^subm]!=INF
        && dp[mask] > dp[mask^subm] + 1){
            dp[mask] = dp[mask^subm] + 1;
            p[mask] = subm;
        }
    }
}

int k = dp[(1<<n)-1];
cout << k << endl;

// Answer recovery
vector<int> color(n);
while(mask>0){
    int mask1 = p[mask];
    for(int i=0; i<n; ++i)
        if(mask1&(1<<i))
            color[i] = k;
    mask ^= mask1;
    --k;
}
