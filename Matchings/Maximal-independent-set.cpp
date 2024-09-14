/**
 * Maximal independent set of a bipartite graph.
 * Firstly, run Kuhn to find maximal matching.
 * First part: 1..n1, second part: n1+1..n1+n2. 
 * mt[v] - v (1<=v<=n1+n2) is matched to mt[v].
 * Maximal independent set: 
 *      v <= n1 (L+): used[v]
 *      v > n1 (R-): !used[v]
*/

auto mis = [&]()->vector<int>{
    used.assign(n1+n2+1, 0);
    auto dfs = [&](int v, auto&& dfs)->void{
        if(used[v]) return;
        used[v] = 1;
        for(auto u : g[v])
            if(u != mt[v]){
                used[u] = 1;
                dfs(mt[u], dfs);
            }
    };
    for(int v=1; v<=n1; ++v){
        if(!mt[v])
            dfs(v, dfs);
    }
    vector<int> res;
    for(int v=1; v<=n1+n2; ++v){
        if((v<=n1 && used[v]) || (v>n1 && !used[v]))
            res.push_back(v);
    }
    return res;
};

