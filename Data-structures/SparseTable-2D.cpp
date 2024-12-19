/**
 * Sparse Table.
 * Sparse2d(a) - build sparse table for a[0][0]..a[n-1][m-1].
 * t[h][i][w][j] - comb(t[i][j]..t[i+(1<<h)-1][j+(1<<w)-1]).
 * comb(x, y) - operation of Sparse table (min, max, &, |, gcd).
 * get(li, lj, ri, rj) - get comb(t[li][lj]..t[ri-1][rj-1]).
 * Complexity: Sparse2d -> O(nm log n * log m), get -> O(1), space -> O(nm log n * log m).
*/

template <class T>
struct Sparse2d{
    const int N=100, M=100, lgN=7, lgM=7;    
    T t[lgN][N][lgM][M];
    Sparse2d(vector<vector<T>> &a){
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
    T get(int li, int lj, int ri, int rj){
        int h = __lg(ri-li), w = __lg(rj-lj);
        int r1 = min(t[h][li][w][lj], t[h][ri-(1<<h)][w][lj]);
        int r2 = min(t[h][li][w][rj-(1<<w)], t[h][ri-(1<<h)][w][rj-(1<<w)]);
        return min(r1,r2);
    }
};