/**
 * DSU class implementation.
 * vertices: 1..n.
 * get(v) - get root of v's set -> O(alpha(n)).
 * unite(v, u) - unite v's and u's sets -> O(alpha(n)).
 * size(v) - get v's set's size.
 * same(v, u) - check if v and u are in the same set.
*/

struct DSU{
    vector<int> p, s;
    DSU(int n){
        p.resize(n+1); s.resize(n+1, 1);
        iota(p.begin(), p.end(), 0);
    }
    int get(int v){
        if(v != p[v])
            p[v] = get(p[v]);     
        return p[v];
    }
    void unite(int v, int u){
        v = get(v);
        u = get(u);
        if(v == u) return;
        if(s[v] < s[u]) swap(v,u);
        p[u] = v;
        s[v] += s[u];    
    }
    int size(int v){
        return s[get(v)];
    }
    bool same(int v, int u){
        return get(v) == get(u);
    } 
};

