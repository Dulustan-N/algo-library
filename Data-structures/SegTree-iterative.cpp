/**
 * Segment Tree iterative.
 * SegTree(n) - segment tree for a[0]..a[n-1].
 * p = 1 is the root, t[p + i] corresponds to segment [a[i], a[i]+1).
 * p: 2*p is left child, 2*p+1 is right child, 
 * p ^ 1 is sibling, p / 2 is parent. 
 * t[p] - value at node p (of segment [l, r)).
 * NONE - neutral element to the operation of SegTree.
 * comb(x, y) - how t[2*p] and t[2*p+1] merge.
 * build(0, 0, n, a) - build segtree of a.
 * upd(q, v) - update a[q] = v;
 * get(ql, qr) - get comb(a[ql]..a[qr-1]).
 * Complexity: build -> O(n), upd -> O(log n), get -> O(log n), space -> O(n log n).
*/

struct SegTree{
    vector<ll> t;
    int n;
    const ll NONE = -INF_LL;
    SegTree(int n) : n(n){t.resize(2*n);}
    auto comb(ll x, ll y){
        return max(x, y);
    }
    void build(const vector<ll> &a){
        for(int i=0; i<n; ++i)
            t[i+n] = a[i];
        for(int p=n-1; p>0; --p)
            t[p] = comb(t[2*p], t[2*p+1]); 
    }
    void upd(int p, ll v){
        p += n;
        t[p] = v;
        for(p/=2; p>0; p/=2)
            t[p] = comb(t[2*p], t[2*p+1]);
    }
    auto get(int l, int r){
        ll res = NONE;        
        for(l+=n, r+=n; l<r; l/=2, r/=2){
            if(l&1) res = comb(res, t[l++]);
            if(r&1) res = comb(res, t[--r]);
        }
        return res;
    }   
};

/**
 * if operation is non-commutative (comb(x,y) != comb(y,x))
 * then get() needs to be modified.
*/
auto get(int l, int r){
    ll resl = NONE, resr = NONE;        
    for(l+=n, r+=n; l<r; l/=2, r/=2){
        if(l&1) resl = comb(resl, t[l++]);
        if(r&1) resr = comb(t[--r], resr);
    }
    return comb(resl, resr);
}   
