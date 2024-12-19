/**
 * Sparse Table.
 * Sparse(a) - build sparse table for a[0]..a[n-1].
 * t[h][i] - comb(t[i]..t[i+(1<<h)-1]).
 * comb(x, y) - operation of Sparse table (min, max, &, |, gcd).
 * get(l, r) - get comb(t[l]..t[r-1]).
 * Complexity: Sparse -> O(n log n), get -> O(1), space -> O(n log n).
*/

template <class T>
struct Sparse{
    vector<vector<T>> t;
    auto comb(T x, T y){
        return min(x, y);
    }
    Sparse(const vector<T> &a){
        int n = a.size(), H = __lg(n);
        t.resize(H+1, vector<T>(n));
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