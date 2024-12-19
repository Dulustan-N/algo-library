/**
 * Segment Tree with lazy range updates.
 * SegTree(n) - segment tree for a[0]..a[n-1].
 * Node p represents segment [l, r): 
 * 2*p+1 is left child, 2*p+2 is right child.
 * t[p] - value at node p (of segment [l, r)).
 * tl[p] - lazy (to be pushed) value at node p.
 * NONE - neutral element to the operation of SegTree.
 * comb(x, y) - how t[2*p+1] and t[2*p+2] merge.
 * apply(p, l, r, v) - apply tl[p] to the node p.
 * push(p, l, r) - push and apply tl[p] to p's children.   
 * build(0, 0, n, a) - build segtree of a.
 * upd(ql, qr, v) - update range a[ql]..a[qr-1] with v.
 * get(ql, qr) - get comb(a[ql]..a[qr-1]).
 * Complexity: build -> O(n), upd -> O(log n), get -> O(log n), space -> O(n log n).
*/

template <class T>
struct SegTree{ 
    vector<T> t;
    vector<T> tl;
    int n;
    const T NONE = 0;
    SegTree(int n) : n(n){t.resize(4*n); tl.resize(4*n);}
    T comb(T a, T b){
        return add(a, b);
    }    
    void apply(int p, int l, int r, T v){
        t[p] = add(t[p], mul(v, r-l));
        tl[p] = add(tl[p], v);
    }
    void push(int p, int l, int r){
        if(tl[p] == NONE) return;
        int m = (l+r)/2;
        apply(2*p+1, l, m, tl[p]);
        apply(2*p+2, m, r, tl[p]);
        tl[p] = NONE;
    }
    void upd(int p, int l, int r, int ql, int qr, T v){
        if(qr<=l || r<=ql) return;
        if(ql<=l && r<=qr){
            apply(p, l, r, v); return; 
        }
        push(p,l,r);
        int m = (l+r)/2;
        upd(2*p+1, l, m, ql, qr, v);
        upd(2*p+2, m, r, ql, qr, v);
        t[p] = comb(t[2*p+1], t[2*p+2]);
    }
    auto get(int p, int l, int r, int ql, int qr){
        if(qr<=l || r<=ql) return NONE;
        if(ql<=l && r<=qr) return t[p];
        push(p, l, r);
        int m = (l+r)/2;
        return comb(get(2*p+1, l, m, ql, qr), get(2*p+2, m, r, ql, qr));
    }   
    void upd(int ql, int qr, T v){
        upd(0, 0, n, ql, qr, v);
    }
    auto get(int ql, int qr){
        return get(0, 0, n, ql, qr);
    }
};
