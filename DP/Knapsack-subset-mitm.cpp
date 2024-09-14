/**
 * "0-1 knapsack with costs" problem:
 * n items with weights w[1]..w[n] and costs c[1]..c[n];
 * fit max cost of items into knapsack of weight capacity W.
 * solve_half(w, c, res) - calculates weights and best costs 
 * for each subset of given w and c, and puts results in res.
 * b_c - cost of max cost mask found.
 * b_mask - max cost mask of items.
 * Complexity: time -> O(2^(n/2) n), space -> O(2^(n/2)).
*/

vector<int> Lw(w.begin(), w.begin()+n/2);
vector<int> Rw(w.begin()+n/2, w.end());
vector<int> Lc(c.begin(), c.begin()+n/2);
vector<int> Rc(c.begin()+n/2, c.end());

auto solve_half = [&](vector<int> w, vector<int> c, vector<pair<ll,ll>> &res)->void{
    int m = w.size();
    for(int mask=0; mask<(1<<m); ++mask){
        ll curw=0, curc=0;
        for(int i=0; i<m; ++i)
            if((mask>>i)&1){
                curw += w[i];
                curc += c[i];
            }
        if(curw <= W)
            res.push_back({curw,curc});
    }
};

vector<pair<ll,ll>> L, R;
solve_half(Lw, Lc, L);
solve_half(Rw, Rc, R);

sort(L.begin(), L.end());

ll curc = -1;
for(auto &[xw,xc] : L){
    curc = max(curc, xc);
    if(xc < curc)
        xc = curc;
}

ll ans=-1;
for(auto &[yw,yc] : R){
    int i = upper_bound(L.begin(), L.end(), make_pair(W-yw, 0ll)) - L.begin() - 1;
    if(i>=0)
        ans = max(ans, L[i].second + yc);
}
cout << ans << endl;

