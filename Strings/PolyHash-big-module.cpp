/**
 * Fast 64-bit Rolling hashing for strings.
 * mod - special fixed 64-bit prime module.
 * p - randomly generated base of hash.
 * mul(x, y) - fast multipication in this module using bit magic.
 * string is s[0..n-1].
 * Hash.get(l, r) - hash of s[l..r] -> O(1).
 * Complexity: time -> O(n).
*/

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const uint64_t mod = (1ull << 61) - 1; 
const uint64_t p = rng() % (mod / 3) + (mod / 3);

struct Hash{
    string s;
    int n;
    vector<uint64_t> h, pi;
    uint64_t add(uint64_t x, uint64_t y){
        return x + y >= mod ? x + y - mod : x + y;
    }
    uint64_t sub(uint64_t x, uint64_t y){
        return add(x, mod - y);
    }    
    int64_t mul(uint64_t a, uint64_t b){
        uint64_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
        uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
        uint64_t ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
        ret = (ret & mod) + (ret >> 61);
        ret = (ret & mod) + (ret >> 61);
        return ret - 1;
    }
    Hash(string _s) : s(_s){
        n = _s.size(); h.resize(n); pi.resize(n);
        h[0] = s[0];
        for(int i=1; i<n; ++i)
            h[i] = add(mul(h[i-1], p), s[i]); 
        pi[0] = 1;
        for(int i=1; i<n; ++i)
            pi[i] = mul(pi[i-1], p);
    }    
    uint64_t get(int l, int r){
        if(l==0) return h[r];
        else return sub(h[r], mul(h[l-1], pi[r-l+1]));                    
    }    
};