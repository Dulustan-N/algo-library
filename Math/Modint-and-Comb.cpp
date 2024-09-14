/**
 * Modint class - numbers in modular arithmetic of mod.
 * Comb class - precomputes factorials and inverse factorials, 
 * comb.bin(a, b) --- choosing b out of a. 
*/

template<int mod>
struct Modint{
	int val;
	Modint() : val(0){};
    Modint(int v) : val(v < 0 ? v + mod : v){};
	Modint(ll v) : val(v % mod){if(val < 0) val += mod;}   

	friend istream& operator>>(istream& in, Modint& a){return in >> a.val;}
	friend ostream& operator<<(ostream& out, Modint a){return out << a.val;}
	friend Modint operator+(Modint a, Modint b){return a.val + b.val >= mod ? a.val + b.val - mod : a.val + b.val;}
	friend Modint operator-(Modint a, Modint b){return a.val - b.val < 0 ? a.val - b.val + mod : a.val - b.val;}
	friend Modint operator*(Modint a, Modint b){return 1ll * a.val * b.val % mod;}
	friend Modint operator/(Modint a, Modint b){return a * inv(b);}
	friend Modint powm(Modint a, ll k){
        Modint res = 1;
        for(; k; k >>= 1, a *= a)
            if(k & 1) res *= a;
        return res; 
    }
	friend Modint inv(Modint a){return powm(a, mod - 2);}
	friend Modint operator-(Modint a){return a.val ? mod - a.val : 0;}
	friend Modint& operator+=(Modint& a, Modint b){return a = a + b;}
	friend Modint& operator-=(Modint& a, Modint b){return a = a - b;}
	friend Modint& operator*=(Modint& a, Modint b){return a = a * b;}
	friend Modint& operator/=(Modint& a, Modint b){return a = a / b;}
	friend Modint& operator++(Modint& a){return a += 1;}
	friend Modint operator++(Modint& a, int){Modint val = a; a += 1; return val;}
	friend Modint& operator--(Modint& a){return a -= 1;}
	friend Modint operator--(Modint& a, int){Modint val = a; a -= 1; return val;}
	friend bool operator==(Modint a, Modint b){return a.val == b.val;}
	friend bool operator!=(Modint a, Modint b){return !(a == b);}
    friend bool operator<(Modint a, Modint b){return a.val < b.val;}
	friend bool operator>(Modint a, Modint b){return a.val > b.val;}

	explicit operator int() const {return val;}
    explicit operator ll() const {return val;}
};

// const int mod = 1e9+7;
const int mod = 998244353;
using mint = Modint<mod>;

struct Comb{
    vector<mint> fac, ifac;
    mint n;
    Comb(int n) : n(n){
        fac.resize(n+1); ifac.resize(n+1);
        fac[0] = 1;
        for(int i=1; i<=n; ++i)
            fac[i] = fac[i-1] * i;
        ifac[n] = inv(fac[n]);
        for(int i=n; i>0; --i)
            ifac[i-1] = ifac[i] * i;
    }
    mint bin(int a, int b){
        if(b<0 || a-b<0) return 0;
        return fac[a] * ifac[b] * ifac[a-b];
    }
} comb(1000000);