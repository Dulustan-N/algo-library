/**
 * Treap (Cartesian tree) with implicit key.
 * key is implicit and equal to a number of nodes to the left (position of the node).
 * Implementation without pointers, not very convenient to use.
 * val - value at a node, 
 * prior - priority of a node,
 * cnt - size of node's subtree,
 * sum - sum of values of node' subtree,
 * min - min of values of node's subtree,
 * add - lazy (delayed) value of node, to be added to all nodes of its subtree.
 * rev - lazy flag to reverse the subtree of the node.
 * l, r - pointers to left and right childs of node.
 * merge(l, r) - merge trees of l and r.
 * split(p, x) - merge tree of p into two parts: l (key < x) and r (key >= x). 
 * insert(p, x, v) - insert value v into tree p at position x (0-based).
 * erase(p, x) - erase element at position x from tree p.
 * add(p, ql, qr, v) - add v to all elements in [ql, qr] in tree p.
 * reverse(p, ql, qr) - reverse [ql,qr) in tree p.
 * get_sum(p, ql, qr) - find sum of elements in [ql, qr) in tree p.
 * get_min(p, ql, qr) - find min of elements in [ql, qr) in tree p.
 * Complexity: everything -> O(log n).
 */

mt19937 rnd(time(0));

struct Treap{
    struct Node{
        int val = 0, prior = 0, cnt = 0;    
        ll sum; int min;
        int add = 0 ;
        bool rev = 0;
        int l = 0, r = 0;
        Node(int _val) : val(_val){
            prior = rnd();
            cnt = 1;
            sum = _val;
            min = _val;
        }
    };
    int root = 0;
    vector<Node> t;
    Treap(){t.push_back(0); t[0].cnt = 0;}

    void upd(int p){
        t[p].cnt = 1 + t[t[p].l].cnt + t[t[p].r].cnt;
        t[p].sum = t[p].val + t[t[p].l].sum + t[t[p].r].sum;
        t[p].min = min({t[p].val, t[t[p].l].min, t[t[p].r].min});
    }
    void add(int p, ll v){
        if(!p) return;
        t[p].add += v;
        t[p].min += v;
        t[p].sum += v * t[p].cnt;
        t[p].val += v;
    }
    void push(int p){
        if(t[p].add){
            add(t[p].l, t[p].add);
            add(t[p].r, t[p].add);  
            t[p].add = 0;
        }     
        if(t[p].rev){
            swap(t[p].l, t[p].r);
            if(t[p].l) t[t[p].l].rev ^= 1;
            if(t[p].r) t[t[p].r].rev ^= 1;
            t[p].rev = 0;
        }
    }
    int merge(int pl, int pr){
        if(!pl) return pr;
        if(!pr) return pl;        
        if(t[pl].prior > t[pr].prior){
            push(pl);
            t[pl].r = merge(t[pl].r, pr);
            upd(pl);
            return pl;
        }
        else{
            push(pr);
            t[pr].l = merge(pl, t[pr].l);
            upd(pr);
            return pr;
        }
    }  
    pair<int, int> split(int p, int x){
        if(!p) return {0,0};
        push(p);
        int cnt = t[t[p].l].cnt;
        if(x > cnt){
            auto [l,r] = split(t[p].r, x-cnt-1);
            t[p].r = l;
            upd(p);
            return {p,r};
        }
        else{
            auto [l,r] = split(t[p].l, x);
            t[p].l = r;
            upd(p);
            return {l,p};
        }
    } 
    void insert(int x, int v){
        auto [l,r] = split(root, x);
        int m = t.size();
        t.push_back(Node(v));    
        root = merge(l, merge(m, r)); 
    }  
    void erase(int x){
        if(t[root].cnt <= x) return; 
        auto [_,r] = split(root, x+1);
        auto [l,m] = split(_, x);
        root = merge(l, r); 
    }
    int get(int k, int p = -1){
        if(p == -1) p = root;
        if(!p) return 0;    
        push(p);
        int cnt = t[t[p].l].cnt;
        if(k == cnt) 
            return p;
        else if(k < cnt) 
            return get(k, t[p].l);
        else
            return get(k-cnt-1, t[p].r);
    }

    ll get_sum(int ql, int qr){
        auto [_,r] = split(root, qr);
        auto [l,m] = split(_, ql);
        ll res = t[m].sum;
        root = merge(l, merge(m, r));
        return res;
    }
    ll get_min(int ql, int qr){
        auto [_,r] = split(root, qr);
        auto [l,m] = split(_, ql);
        ll res = t[m].min;
        root = merge(l, merge(m, r));
        return res;
    }
    void add(int ql, int qr, ll v){
        auto [_,r] = split(root, qr); 
        auto [l,m] = split(_, ql); 
        add(m, v);
        root = merge(l, merge(m, r));
    }
    void reverse(int ql, int qr){
        auto [_,r] = split(root, qr); 
        auto [l,m] = split(_, ql); 
        t[m].rev ^= 1;
        root = merge(l, merge(m, r));
    }
    void print(int p = -1){
        if(p == -1) p = root;
        if(!p) return;
        push(p);
        print(t[p].l);
        cout << " " << t[p].val << " ";
        print(t[p].r);
    }
};