/**
 * Two-dimensional Fenwick Tree (Binary Indexed Tree).
 * Internally 1-based index, but interface is 0-based.
 * Fenwick(n, m) - fenwick tree for a[y][x]: 0 <= y < n, 0 <= x < m.
 * upd(y, x, v) - update a[y][x] += v.
 * get(ly, lx, ry, rx) - get a[ly][lx]+..+a[ry-1][rx-1].
 * Complexity: upd -> O(log n * log m), 
 *          get -> O(O(log n * log m)), space -> O(nm log n * log m). 
*/

template<class T>
struct Fenwick2d{
    int n,m;
    vector<vector<T>> t;
    Fenwick2d(int n, int m) : n(n), m(m){
        t.resize(n+1, vector<T>(m+1));
    }
    void upd(int y, int x, T v){
        for(int i=y+1; i<=n; i+=i&(-i))
            for(int j=x+1; j<=m; j+=j&(-j))
                t[i][j] += v;
    }    
    T get(int y, int x){
        T res = 0;
        for(int i=y+1; i>0; i-=i&(-i))
            for(int j=x+1; j>0; j-=j&(-j))
                res += t[i][j];
        return res;
    }
    T get(int ly, int lx, int ry, int rx){
        return get(ry-1,rx-1) - get(ly-1,rx-1)
                - get(ry-1,lx-1) + get(ly-1,lx-1);
    }
};