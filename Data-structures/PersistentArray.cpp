/**
 * Fully persistent array build on persistent segment tree.
 * PerArray(n) - persistent array for 0..n-1.
 * Node p represents segment [l, r): 
 * ch[p].first is left child, ch[p].second is right child.
 * t[p] - value at leaf node p (non-leafs have value zero).
 * build(0, 0, n, a) - build tree for arary a[0]..a[n-1].
 * upd(p, q, v) - update a[q] = v from root p and return the root of the new version.
 * get(p, q) - get a[q] from root p.
 * need to use separate array ver[]:
 * ver[i] - root of version i.
 * Complexity: build -> O(n), upd -> O(log n), get -> O(log n), space -> O(n log n).
*/

struct PerArray{
    vector<ll> t;
    vector<pair<int,int>> ch;
    int n;
    PerArray(int n) : n(n){
        //t.reserve(1e7); ch.reserve(1e7);
    }
    int build(int l, int r, const vector<ll> &a){
        int p = t.size();
        t.push_back(a[l]);
        ch.push_back({-1,-1});
        if(r-l == 1){t[p] = a[l]; return p;}
        int m = (l+r)/2;
        ch[p].first = build(l, m, a);
        ch[p].second = build(m, r, a);
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
        return np;
    }
    auto get(int p, int l, int r, int q){
        if(r-l==1) return t[p];
        int m = (l+r)/2;
        if(q < m) 
            return get(ch[p].first, l, m, q);
        else 
            return get(ch[p].second, m, r, q);
    }    
    auto upd(int p, int q, int v){
        return upd(p, 0, n, q, v);
    }
    auto get(int p, int q){
        return get(p, 0, n, q);
    }
};