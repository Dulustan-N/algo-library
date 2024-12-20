/**
 * O(n log n) Number Theoretic Transformation
 * c = conv(a, b) - convolution of a and b:
 * c[i] = (a[0]*b[i] + a[1]*b[i-1] + ... + a[i]*b[0]) % mod.
 * mod = 998244353 = 119 * (2 ^ 23) + 1
 * a.size = n, b.size = m, c.size = n + m - 1
 * Complexity: time -> O(n+m), space -> O((n+m) log(n+m)).
*/

const int MOD = 998244353;

int add(int a, int b, int mod = MOD){return a + b >= mod ? a + b - mod : a + b;}
int sub(int a, int b, int mod = MOD){return a - b < 0 ? a - b + mod : a - b;}
int mul(int a, int b, int mod = MOD){return (ll)a * b >= mod ? (ll)a * b % mod : a * b;}
int powm(int a, ll k, int mod = MOD){
    int res = 1;
    for(; k; k >>= 1, a = mul(a, a))
        if(k & 1) res = mul(res, a);
    return res;
}
int inv(int a, int mod = MOD){return powm(a, mod - 2);}
int divi(int a, int b, int mod = MOD){return mul(a, inv(b, mod));}
void chadd(int &a, int b, int mod = MOD){a = add(a, b, mod);}
void chsub(int &a, int b, int mod = MOD){a = sub(a, b, mod);}
void chmul(int &a, int b, int mod = MOD){a = mul(a, b, mod);}
void chdivi(int &a, int b, int mod = MOD){a = divi(a, b, mod);}


struct FFT{
    int mod, root, iroot, root_pw;
    vector<int> roots, iroots;
    FFT(int mod = 998244353){
        root = 3; iroot = 332748118; root_pw = 23;
        roots.resize(root_pw); iroots.resize(root_pw);
        roots[0] = powm(root, 119);
        iroots[0] = powm(iroot, 119);
        for(int i=1; i<root_pw; ++i){
            roots[i] = mul(roots[i-1], roots[i-1], mod);
            iroots[i] = mul(iroots[i-1], iroots[i-1], mod);
        }
    }
    void dft(vector<int> &a, bool invert = 0){
        int n = a.size();
        for(int i=1, j=0; i<n; ++i){
            int bit = n >> 1;
            for(; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if(i < j) swap(a[i], a[j]);
        }        
        for(int len=2, pw=1; len<=n; len<<=1, ++pw){
            int wlen = invert ? iroots[root_pw-pw] : roots[root_pw-pw];
            for(int i=0; i<n; i+=len){
                int w = 1;
                for(int j=0; j<len/2; ++j){
                    int u = a[i+j], v = mul(a[i+j+len/2], w);
                    a[i+j] = add(u, v);
                    a[i+j+len/2] = sub(u, v);
                    chmul(w, wlen);
                }
            }
        }
        if(invert){
            int n_inv = inv(n);
            for(int &x : a) chmul(x, n_inv);
        }
    }
    vector<int> conv(vector<int> &a, vector<int> &b){
        int n = a.size(), m = b.size(), s = 1;
        while(s < n+m-1) s <<= 1;
        vector<int> fa = a, fb = b;
        fa.resize(s); fb.resize(s);
        dft(fa), dft(fb);
        for(int i=0; i<s; ++i) chmul(fa[i], fb[i]);
        dft(fa, 1);
        fa.resize(n+m-1);   
        return fa;
    }    
} fft;