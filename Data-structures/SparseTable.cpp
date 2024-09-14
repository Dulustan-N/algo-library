/**
 * Sparse Table.
 * Sparse(a) - build sparse table for a[0]..a[n-1].
 * t[h][i] - comb(t[i]..t[i+(1<<h)-1]).
 * comb(x, y) - operation of Sparse table (min, max, &, |, gcd).
 * get(l, r) - get comb(t[l]..t[r-1]).
 * Complexity: Sparse -> O(n log n), get -> O(1), space -> O(n log n).
*/

struct Sparse{
    vector<vector<ll>> t;
    auto comb(ll x, ll y){
        return min(x, y);
    }
    Sparse(const vector<ll> &a){
        int n = a.size(), H = __lg(n);
        t.resize(H+1, vector<ll>(n));
        for(int i=0; i<n; ++i)
            t[0][i] = a[i];
        for(int h=1; h<=H; ++h)
            for(int i=0; i+(1<<h)<=n; ++i)
                t[h][i] = comb(t[h-1][i], t[h-1][i+(1<<(h-1))]); 
    }
    auto get(int l, int r){
        int h = __lg(r-l);
        return comb(t[h][l], t[h][r-(1<<h)]);
    }
};


//2D Sparse Table

struct Sparse2{
    const int N=100, M=100, lgN=7, lgM=7;    
    int t[lgN][N][lgM][M];
    Sparse(const vector<vector<ll>> &a){
        int n = a.size(), H = __lg(n);
        int m = a[0].size(), W = __lg(m);
        for(int i=0; i<n; ++i){
            for(int j=0; j<m; ++j)
                t[0][i][0][j] = a[i][j];
            for(int w=1; w<=W; ++w)
                for(int j=0; j+(1<<w)<=m; ++j)
                    t[0][i][w][j] = min(t[0][i][w-1][j], 
                    t[0][i][w-1][j+(1<<(w-1))]);                
        }
        for(int h=1; h<=H; ++h)
            for(int i=0; i+(1<<h)<=n; ++i)
                for(int w=0; w<=W; ++w)
                    for(int j=0; j+(1<<w)<=m; ++j)
                        t[h][i][w][j] = min(t[h-1][i][w][j], 
                                t[h-1][i+(1<<(h-1))][w][j]);
    }    
    auto get(int li, int lj, int ri, int rj){
        int h = __lg(ri-li), w = __lg(rj-lj);
        int r1 = min(t[h][li][w][lj], t[h][ri-(1<<h)][w][lj]);
        int r2 = min(t[h][li][w][rj-(1<<w)], t[h][ri-(1<<h)][w][rj-(1<<w)]);
        return min(r1,r2);
    }
};

void solve(){    
    int n,m; cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m));
    forn(i,0,n)
        forn(j,0,m)
            cin >> a[i][j];                
    Sparse2 sp(a);
}

