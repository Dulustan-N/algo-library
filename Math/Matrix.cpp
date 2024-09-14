/**
 * Very simple matrix implementation
 * mulm(X, Y) --- mod multiplication of X and Y.
 * powm(X, k) --- X in power k in mod. 
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


using mat = vector<vector<int>>;
mat I{{1,0},{0,1}};
mat mulm(mat X, mat Y){
    int n = X.size(), m = X[0].size(), k = Y[0].size();
    assert(m == (int)Y.size());
    mat Z(n, vector<int>(k));
    for(int i=0; i<n; ++i)
        for(int j=0; j<k; ++j)
            for(int t=0; t<m; ++t)
                Z[i][j] = add(Z[i][j], mul(X[i][t], Y[t][j]));
    return Z;
}
mat powm(mat X, ll k){
    mat res = I;
    for(; k; k >>= 1){
        if(k & 1) res = mulm(res, X);
        X = mulm(X, X);
    }
    return res;     
}