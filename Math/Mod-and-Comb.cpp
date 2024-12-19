/**
 * Modular arithmetic and combinatorics.
 * Comb class - precomputes factorials and inverse factorials, 
 * comb.nCr(a, b) --- choosing b out of a. 
 * comb.nPr(a, b) --- choosing b with order out of a.
*/

// const int mod = 1e9+7;
const int mod = 998244353;

int add(int a, int b){return a + b >= mod ? a + b - mod : a + b;}
int sub(int a, int b){return a - b < 0 ? a - b + mod : a - b;}
int mul(int a, int b){return (ll)a * b >= mod ? (ll)a * b % mod : a * b;}
int powm(int a, ll k){
    int res = 1;
    for(; k; k >>= 1, a = mul(a, a))
        if(k & 1) res = mul(res, a);
    return res;
}
int inv(int a){return powm(a, mod - 2);}
int divi(int a, int b){return mul(a, inv(b));}
void chadd(int &a, int b){a = add(a, b);}
void chsub(int &a, int b){a = sub(a, b);}
void chmul(int &a, int b){a = mul(a, b);}
void chdivi(int &a, int b){a = divi(a, b);}


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