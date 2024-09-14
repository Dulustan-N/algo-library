/**
 * Segment Tree Beats example.
 * Problem: array a[0],..,a[n-1]. 3 kinds of queries:
 * 1: a[i] = x, 2: a[i] %=  x for l<=i<=r, 3: a[l]+..a[r] = ?
*/

struct SegTree{      
    struct Node{
        ll sum, max, min, lz;
    };  
    vector<Node> t;
    int n;
    const Node NONE = {0, -INF_LL, INF_LL, -1}; 
    SegTree(int n) : n(n){t.resize(4*n);}   
    Node comb(Node a, Node b){
        return {a.sum + b.sum, max(a.max, b.max),
            min(a.min, b.min), -1};
    }    
    void apply(int p, int l, int r, ll v){
        t[p].sum = v * (r-l);
        t[p].max = t[p].min = v;
        t[p].lz = v;
    }
    void push(int p, int l, int r){
        if(t[p].lz == -1) return;
        int m = (l+r)/2;
        apply(2*p+1, l, m, t[p].lz);
        apply(2*p+2, m, r, t[p].lz);
        t[p].lz = -1;
    }
    void build(int p, int l, int r, const vector<ll> &a){
        if(r-l==1){t[p] = {a[l], a[l], a[l], -1}; return;}
        int m = (l+r)/2;
        build(2*p+1, l, m, a);
        build(2*p+2, m, r, a);
        t[p] = comb(t[2*p+1], t[2*p+2]);
    }
    void upd(int p, int l, int r, int ql, int qr, ll v){
        if(qr<=l || r<=ql || t[p].max < v) return; //break condition
        if(ql<=l && r<=qr && t[p].min == t[p].max){ //tag condition
            apply(p, l, r, t[p].max % v); return; 
        }
        push(p, l, r);
        int m = (l+r)/2;
        upd(2*p+1, l, m, ql, qr, v);
        upd(2*p+2, m, r, ql, qr, v);
        t[p] = comb(t[2*p+1], t[2*p+2]);
    }
    void upd_val(int p, int l, int r, int q, ll v){
        if(r-l==1){
            t[p] = {v, v, v, -1}; return;
        }
        int m = (l+r)/2;
        if(q<m) upd_val(2*p+1, l, m, q, v);
        else upd_val(2*p+2, m, r, q, v);
        t[p] = comb(t[2*p+1], t[2*p+2]);
    }
    Node get(int p, int l, int r, int ql, int qr){
        if(qr<=l || r<=ql) return NONE;
        if(ql<=l && r<=qr) return t[p];
        push(p,l,r);
        int m = (l+r)/2;
        return comb(get(2*p+1,l,m,ql,qr), get(2*p+2,m,r,ql,qr));
    }   
    void upd(int ql, int qr, ll v){
        upd(0, 0, n, ql, qr, v);
    }
    void add(int ql, int qr, ll v){
        add(0, 0, n, ql, qr, v);
    }
    auto get(int ql, int qr){
        return get(0, 0, n, ql, qr);
    }
};
