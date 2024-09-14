/**
 * Segment Tree simple.
 * SegTree(n) - segment tree for a[0]..a[n-1].
 * Node p represents segment [l, r): 
 * ch[p].first is left child, ch[p].second is right child.
 * t[p] - value at node p (of segment [l, r)).
 * NONE - neutral element to the operation of SegTree.
 * comb(x, y) - how t[2*p+1] and t[2*p+2] merge.
 * build(0, 0, n, a) - build segtree of a and return its root.
 * upd(p, q, v) - update a[q] = v from root and return the root of the new version.
 * get(p, ql, qr) - get comb(a[ql]..a[qr-1]) from root p.
 * need to use separate array ver[]:
 * ver[i] - number of root of version i.
 * Complexity: build -> O(n), upd -> O(log n), get -> O(log n), space -> O(n log n).
*/

struct SegTree{
    vector<ll> t;
    vector<pair<int,int>> ch;
    int n;
    const ll NONE = 0; 
    SegTree(int n) : n(n){
        //t.reserve(1e7); ch.reserve(1e7);
    }
    auto comb(ll x, ll y){
        return max(x, y);
    }
    int build(int l, int r, const vector<ll> &a){
        int p = t.size();
        t.push_back(a[l]);
        ch.push_back({-1,-1});
        if(r-l == 1){t[p] = a[l]; return p;}
        int m = (l+r)/2;
        ch[p].first = build(l, m, a);
        ch[p].second = build(m, r, a);
        t[p] = comb(t[ch[p].first], t[ch[p].second]);
        return p;
    }
    int upd(int p, int l, int r, int q, int v){
        int np = t.size();
        t.push_back(t[p]);
        ch.push_back(ch[p]);
        if(r-l == 1){t[np] = v; return np;}
        int m = (l+r)/2;
        if(q < m) 
            ch[np].first = upd(ch[p].first, l, m, q, v);
        else 
            ch[np].second = upd(ch[p].second, m, r, q, v);
        t[np] = comb(t[ch[np].first], t[ch[np].second]);
        return np;
    }
    auto get(int p, int l, int r, int ql, int qr){
        if(l>=qr || ql>=r) return NONE;
        if(ql<=l && r<=qr) return t[p];
        int m=(l+r)/2;
        return comb(get(ch[p].first, l, m, ql, qr),
                    get(ch[p].second, m, r, ql, qr));
    }    
    auto upd(int p, int q, int v){
        return upd(p, 0, n, q, v);
    }
    auto get(int p, int ql, int qr){
        return get(p, 0, n, ql, qr);
    }
};

vector<int> ver;