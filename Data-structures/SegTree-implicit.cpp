/**
 * Segment Tree Implicit (Dynamic / Sparse).
 * SegTree(n) - segment tree for range [0..n).
 * Node p represents segment [l, r): 
 * ch[p].first is left child, ch[p].second is right child.
 * t[p] - value at node p (of segment [l, r)).
 * NONE - neutral element to the operation of SegTree.
 * comb(x, y) - how t[2*p+1] and t[2*p+2] merge.
 * build(0, 0, n, a) - build segtree of a.
 * extend(p) - before going to children of p make sure they exist.
 * upd(q, v) - update a[q] = v.
 * get(ql, qr) - get comb(a[ql]..a[qr-1]).
 * Complexity: build -> O(n), upd -> O(log n), get -> O(log n), space -> O(n log n).
*/

template <class T>
struct SegTree{
    vector<T> t;
    vector<pair<int,int>> ch;
    int n;
    const T NONE = 0; 
    SegTree(int n) : n(n){
        //t.reserve(1e7); ch.reserve(1e7);
        t.push_back(NONE);
        ch.push_back({-1,-1});  
    }
    T comb(T x, T y){
        return max(x, y);
    }
    void extend(int p){
        if(ch[p].first == -1){
            ch[p].first = t.size();
            t.push_back(NONE);
            ch.push_back({-1,-1});            
        }
        if(ch[p].second == -1){
            ch[p].second = t.size();
            t.push_back(NONE);
            ch.push_back({-1,-1});            
        }
    }
    void upd(int p, int l, int r, int q, T v){
        if(r-l==1){t[p] += v; return;}
        extend(p);
        int m = (l+r)/2;
        if(q<m) 
            upd(ch[p].first, l, m, q, v);
        else 
            upd(ch[p].second, m, r, q, v);
        t[p] = comb(t[ch[p].first], t[ch[p].second]);
    }
    T get(int p, int l, int r, int ql, int qr){
        if(l>=qr || ql>=r) return NONE;
        if(ql<=l && r<=qr) return t[p];
        extend(p);
        int m = (l+r)/2;
        return comb(get(ch[p].first, l, m, ql, qr),
                    get(ch[p].second, m, r, ql, qr));
    }    
    auto upd(int q, T v){
        return upd(0, 0, n, q, v);
    }
    T get(int ql, int qr){
        return get(0, 0, n, ql, qr);
    }
};
