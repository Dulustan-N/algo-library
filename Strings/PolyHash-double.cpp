/**
 * Double rolling hashing for strings (Rabin-Karp algorithm).
 * Build in O(n), one query in O(1).
 * Two fixed prime modules, two randomly generated bases.
 * mod - pair of modules.
 * p - pair of bases.
 * string is s[0..n-1].
 * Hash.get(l, r) - double hash of s[l..r] -> O(1).
 * Complexity: time -> O(n).
*/

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const pair<int,int> mod = {1e9+7, 1e9+123}; 
const pair<int,int> p = {rng() % (mod.F / 3) + mod.F / 3, 
                         rng() % (mod.S / 3) + mod.S / 3};

struct Hash{
    string s;
    int n;
    vector<pair<int,int>> h, pi;
    pair<int,int> add(pair<int,int> x, pair<int,int> y){
        return {x.F + y.F >= mod.F ? x.F + y.F - mod.F : x.F + y.F, 
                x.S + y.S >= mod.S ? x.S + y.S - mod.S : x.S + y.S};
    }
    pair<int,int> sub(pair<int,int> x, pair<int,int> y){
        return {x.F - y.F < 0 ? x.F - y.F + mod.F : x.F - y.F, 
                x.S - y.S < 0 ? x.S - y.S + mod.S : x.S - y.S};
    }
    pair<int,int> mul(pair<int,int> x, pair<int,int> y){
        return {x.F * 1ll * y.F % mod.F, x.S * 1ll * y.S % mod.S};
    }
    Hash(string _s) : s(_s){
        n = _s.size(); h.resize(n); pi.resize(n);
        h[0] = {s[0], s[0]};
        for(int i=1; i<n; ++i)
            h[i] = add(mul(h[i-1], p), {s[i],s[i]}); 
        pi[0] = {1, 1};
        for(int i=1; i<n; ++i)
            pi[i] = mul(pi[i-1], p);
    }    
    pair<int,int> get(int l, int r){
        if(l==0) return h[r];
        else return sub(h[r], mul(h[l-1], pi[r-l+1]));                    
    }    
};