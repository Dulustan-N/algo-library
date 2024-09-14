/**
 * Fenwick Tree (Binary Indexed Tree) for max on prefixes.
 * Internally 1-based index, but interface is 0-based.
 * Fenwick(n) - fenwick tree for a[0]..a[n-1].
 * upd(i, v) - update a[i] = max(a[i], v).
 * get(i) - get max(a[0],..,a[i]).
 * Complexity: upd -> O(log n), get -> O(log n), space -> O(n log n). 
*/


template<class T>
struct Fenwick{
    vector<ll> t;
    Fenwick(int n){t.resize(n+1);}
    void upd(int i, ll v){
        for(++i; i<t.size(); i+=i&(-i))
            t[i] = max(t[i], v);
    }    
    ll get(int i){
        ll res=0;
        for(++i; i>0; i-=i&(-i))
            res = max(res, t[i]);
        return res;
    }
};
