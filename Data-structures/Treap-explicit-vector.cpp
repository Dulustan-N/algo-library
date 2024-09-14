/**
 * Treap (Cartesian tree) with explicit key. 
 * Implementation without pointers, not very convenient to use.
 * key - key at a node, 
 * prior - priority of a node,
 * cnt - size of node's subtree,
 * sum - sum of keys of node' subtree,
 * l, r - pointers to left and right childs of node.
 * find(p, x) - find node with key = x.
 * merge(l, r) - merge trees of l and r.
 * split(p, x) - merge tree of p into two parts: l (key < x) and r (key >= x). 
 * insert(p, x) - insert key x into tree p.
 * erase(p, x) - erase key x from tree p.
 * find_kth(p, x) - find kth element (0-based number) by order in tree p.
 * get_sum(p, ql, qr) - find sum of elements in [ql, qr) in tree p.
 * Complexity: everything -> O(log n).
 */

mt19937 rnd(time(0));

struct Treap{
    struct Node{
        int key, prior;
        int cnt = 0; 
        ll sum = 0;  
        int l = 0, r = 0;
        Node(int _key) : key(_key){
            prior = rnd();
            sum = _key;
        }
    };
    int root = 0;
    vector<Node> t;
    Treap(){t.push_back(0); t[0].cnt = 0;}

    void upd(int p){
        t[p].cnt = 1 + t[t[p].l].cnt + t[t[p].r].cnt;
        t[p].sum = t[p].key + t[t[p].l].sum + t[t[p].r].sum;
    }
    int find(int x, int p = -1){
        if(p == -1) p = root;
        if(!p) return 0;
        if(t[p].key == x) 
            return p;
        if(t[p].key > x)
            return find(x, t[p].l);
        else
            return find(x, t[p].r);
    }
    int merge(int pl, int pr){
        if(!pl) return pr;
        if(!pr) return pl;        
        if(t[pl].prior > t[pr].prior){
            t[pl].r = merge(t[pl].r, pr);
            upd(pl);
            return pl;
        }
        else{
            t[pr].l = merge(pl, t[pr].l);
            upd(pr);
            return pr;
        }
    }  
    pair<int, int> split(int p, int x){
        if(!p) return {0,0};
        if(t[p].key < x){
            auto [l,r] = split(t[p].r, x);
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
    void insert(int x){
        if(find(x)) return; //для уникальных ключей
        auto [l,r] = split(root, x);
        int m = t.size();
        t.push_back(Node(x)); 
        root = merge(l, merge(m, r)); 
    }  
    void erase(int x){
        if(!find(x)) return;
        auto [_,r] = split(root, x+1);
        auto [l,m] = split(_, x);
        root = merge(l, r); 
    }
    int find_kth(int k, int p = -1){
        if(p == -1) p = root;
        if(!p) return 0;    
        int cnt = t[t[p].l].cnt;
        if(k == cnt) 
            return p;
        else if(k < cnt) 
            return find_kth(k, t[p].l);
        else
            return find_kth(k-cnt-1, t[p].r);
    }
    ll get_sum(int p, int ql, int qr){
        auto [_,r] = split(p, qr);
        auto [l,m] = split(_, ql);
        ll res = t[m].sum;
        p = merge(l, merge(m, r));
        return res;
    }
    void print(int p = -1){
        if(p == -1) p = root;
        if(!p) return;
        print(t[p].l);
        cout << " " << t[p].key << " ";
        print(t[p].r);
    }
};