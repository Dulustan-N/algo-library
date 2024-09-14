/**
 * DSU class implementation with rollbacks.
 * get(v) - get root of v's set -> O(log n).
 * unite(v, u) - unite v's and u's sets -> O(log n).
 * size(v) - get v's set's size.
 * same(v, u) - check if v and u are in the same set.
 * rollback() - rollback one change.
 * hsz() - get hist size (to know when to stop rollbacks).
*/

struct DSU{
    vector<int> p, s;
    vector<pair<int &, int>> hist;
    DSU(int n){
        p.resize(n+1); s.resize(n+1, 1);
        iota(p.begin(), p.end(), 0);
    }
    int get(int v){
        if(v != p[v])
            v = get(p[v]);     
        return p[v];
    }
    void unite(int v, int u){
        v = get(v);
        u = get(u);
        if(v == u) return;
        if(s[v] < s[u]) swap(v,u);
        hist.push_back({s[v], s[v]});    
        hist.push_back({p[u], p[u]}); 
        p[u] = v;
        s[v] += s[u];           
    }
    int size(int v){
        return s[get(v)];
    }
    bool same(int v, int u){
        return get(v) == get(u);
    } 
    int hsz(){return hist.size();}
    void rollback(){
        hist.back().first = hist.back().second;
        hist.pop_back();
        hist.back().first = hist.back().second;
        hist.pop_back();
    }
};