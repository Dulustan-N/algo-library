/**
 * Fenwick Tree (Binary Indexed Tree).
 * Internally 1-based index, but interface is 0-based.
 * Fenwick(n) - fenwick tree for a[0]..a[n-1].
 * upd(i, v) - update a[i] += v.
 * get(l, r) - get a[l]+..+a[r-1].
 * lower_bound(v) - find min i: a[0]+..+a[i] >= v,
 * by binary lifting -> O(log n).
 * Complexity: upd -> O(log n), get -> O(log n), space -> O(n log n). 
*/

template <class T>
struct Fenwick{
    vector<T> t;
    Fenwick(int n){t.resize(n+1);}
    void upd(int i, T v){        
        for(++i; i<(int)t.size(); i+=i&(-i))
            t[i] += v;
    }    
    auto get(int i){
        T res = 0;
        for(++i; i>0; i-=i&(-i))
            res += t[i];
        return res;
    }
    auto get(int l, int r){
        return get(r-1) - (l ? get(l-1) : 0);
    }     
};

//Binary lifting
int lower_bound(T v){
    T sum = 0; 
    int pos = 0;        
    for(int i=__lg(t.size()); i>=0; --i){
        if(pos+(1<<i) < t.size() && sum+t[pos+(1<<i)] < v){
            sum += t[pos+(1<<i)];
            pos += (1<<i);
        }
    }
    return pos; 
}