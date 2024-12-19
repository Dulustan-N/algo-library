/**
 * Segment Tree simple.
 * SegTree(n) - segment tree for a[0]..a[n-1].
 * Node p represents segment [l, r): 
 * 2*p+1 is left child, 2*p+2 is right child.
 * t[p] - value at node p (of segment [l, r)).
 * NONE - neutral element to the operation of SegTree.
 * comb(x, y) - how t[2*p+1] and t[2*p+2] merge.
 * build(0, 0, n, a) - build segtree of a.
 * upd(q, v) - update a[q] = v;
 * get(ql, qr) - get comb(a[ql]..a[qr-1]).
 * Complexity: build -> O(n), upd -> O(log n), get -> O(log n), space -> O(n log n).
*/

template<class T>
struct SegTree{        
    vector<T> t;
    int n;
    const T NONE = -INF_LL; 
    SegTree(int n) : n(n){t.resize(4*n);}
    T comb(T x, T y){
        return max(x, y);
    }
    void build(int p, int l, int r, const vector<T> &a){
        if(r-l==1){t[p] = a[l]; return;}
        int m = (l+r)/2;
        build(2*p+1, l, m, a);
        build(2*p+2, m, r, a);
        t[p] = comb(t[2*p+1], t[2*p+2]);
    }
    void upd(int p, int l, int r, int q, T v){
        if(r-l==1){t[p] = v; return;}
        int m = (l+r)/2;
        if(q<m) upd(2*p+1, l, m, q, v);
        else upd(2*p+2, m, r, q, v);
        t[p] = comb(t[2*p+1], t[2*p+2]);
    }
    auto get(int p, int l, int r, int ql, int qr){
        if(l>=qr || ql>=r) return NONE;
        if(ql<=l && r<=qr) return t[p];
        int m = (l+r)/2;
        return comb(get(2*p+1, l, m, ql, qr),
                    get(2*p+2, m, r, ql, qr));
    }    
    void upd(int q, T v){
        upd(0, 0, n, q, v);
    }
    auto get(int ql, int qr){
        return get(0, 0, n, ql, qr);
    }
};

/**
 * first_above(0, 0, n, q, v) - min i>=q such that 
 *      a[i]>=v, works only for SegTree with max.
 * get_kth(0, 0, n, k) - get kth one in binary array a[0..n-1],
 *      works only for SegTree with sum.
*/
int first_above(int p, int l, int r, int q, T v){
    if(t[p] < v || r <= q) return -1;
    if(r-l == 1) return l;
    int m = (l+r)/2;
    int x = -1;
    if(t[2*p+1] >= v)
        x = first_above(2*p+1, l, m, q, v);
    if(x == -1) 
        x = first_above(2*p+2, m, r, q, v);
    return x;
}

int get_kth(int p, int l, int r, int k){
    if(t[p] < k) return -1;
    if(r-l == 1) return l;
    int m = (l+r)/2;
    if(t[2*p+1] >= k)
        return get_kth(2*p+1, l, m, k);
    else
        return get_kth(2*p+2, m, r, k-t[2*p+1]);
} 
