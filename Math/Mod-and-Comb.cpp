/**
 * Modular arithmetic and combinatorics.
 * Comb class - precomputes factorials and inverse factorials, 
 * comb.nCr(a, b) --- choosing b out of a. 
 * comb.nPr(a, b) --- choosing b with order out of a.
*/

// const int MOD = 1e9+7;
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


struct Comb{
    vector<int> fac, ifac;
    int n;
    Comb(int n) : n(n){
        fac.resize(n+1); ifac.resize(n+1);
        fac[0] = 1;
        for(int i=1; i<=n; ++i)
            fac[i] = mul(fac[i-1], i);
        ifac[n] = inv(fac[n]);
        for(int i=n; i>0; --i)
            ifac[i-1] =  mul(ifac[i], i);
    }
    int bin(int a, int b){
        if(b < 0 || a - b < 0) return 0;
        return mul(mul(fac[a], ifac[b]), ifac[a-b]);
    }
} comb(1000000);