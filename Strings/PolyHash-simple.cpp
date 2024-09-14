/**
 * Rolling hashing for strings (Rabin-Karp algorithm).
 * Build in O(n), one query in O(1).
 * mod - fixed prime module.
 * p - randomly generated base of hash.
 * string is s[0..n-1].
 * Hash.get(l, r) - hash of s[l..r] -> O(1).
 * Complexity: time -> O(n).
*/

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int mod = 1e9+7; 
const int p = rng() % (mod / 3) + (mod / 3);

struct Hash{
    string s;
    int n;
    vector<int> h, pi;
    int add(int x, int y){
        return x + y >= mod ? x + y - mod : x + y;
    }
    int sub(int x, int y){
        return x - y < 0 ? x - y + mod : x - y;
    }    
    Hash(string _s) : s(_s){
        n = _s.size(); h.resize(n); pi.resize(n);
        h[0] = s[0];
        for(int i=1; i<n; ++i)
            h[i] = add(h[i-1] * 1ll * p % mod, s[i]); 
        pi[0] = 1;
        for(int i=1; i<n; ++i)
            pi[i] = pi[i-1] * 1ll * p % mod;
    }    
    int get(int l, int r){
        if(l==0) return h[r];
        else return sub(h[r], h[l-1] * 1ll * pi[r-l+1] % mod);                    
    }    
};
