/**
 * Dynamic Connectivity Problem offline:
 * queries of adding edge, removing edge,
 * queries of asking how many connected components currently.
 * Complexity -> O(m log^2 m).
*/

struct DSU{
    vector<int> p, s;
    vector<pair<int &, int>> hist;
    void init(int n){
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

vector<int> query, ans;
struct DCP{        
    vector<vector<pair<int,int>>> t;
    DSU dsu;
    int n, cnt;
    DCP(int n, int cnt) : n(n), cnt(cnt){t.resize(4*n); dsu.init(cnt);}    
    void upd(int p, int l, int r, int ql, int qr, pair<int,int> edge){
        if(l>=qr || ql>=r) return;
        if(ql<=l && r<=qr){
            t[p].push_back(edge); return;
        }
        int m = (l+r)/2;
        upd(2*p+1, l, m, ql, qr, edge);
        upd(2*p+2, m, r, ql, qr, edge);
    }  
    void upd(int ql, int qr, pair<int,int> edge){
        upd(0, 0, n, ql, qr, edge);
    }
    void calc(int p, int l, int r){
        int snap = dsu.hist.size();
        for(auto [v,u] : t[p]){
            if(!dsu.same(v,u)){
                dsu.unite(v,u);
                --cnt;
            }            
        }        
        if(r-l == 1 && query[l]){
            ans.push_back(cnt);
        }
        else if(r-l > 1){
            int m = (l+r)/2;
            calc(2*p+1, l, m);
            calc(2*p+2, m, r);
        }
        while(dsu.hsz() > snap){
            dsu.rollback();
            ++cnt;
        }        
    }
};

void solve(){
    int n,m; cin >> n >> m;
    DCP dcp(m, n);
    map<pair<int,int>, int> added;
    query.assign(m, 0);
    for(int i=0; i<m; ++i){
        char req; cin >> req;
        if(req == '+'){
            int v,u; cin >> v >> u;
            if(v>u) swap(v,u);
            if(added.count({v,u})) continue;
            added[{v,u}] = i;
        }
        else if(req == '-'){
            int v,u; cin >> v >> u;
            if(v>u) swap(v,u);
            int l = added[{v,u}];
            dcp.upd(l,i,{v,u});
            added.erase(added.find({v,u}));
        }
        else{
            query[i] = 1;
        }
    }
    for(auto [_,l] : added){
        auto [v,u] = _;
        dcp.upd(l,m,{v,u});
    }

    dcp.calc(0, 0, m);
    for(auto x : ans)
        cout << x << "\n";
}
