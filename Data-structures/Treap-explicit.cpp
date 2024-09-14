/**
 * Treap (Cartesian tree) with explicit key.
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

struct Node{
    int key, prior;
    int cnt=1; 
    ll sum;  
    Node *l=0, *r=0;
    Node(int _key) : key(_key){
        prior = rnd();
        sum = _key;
    }
    ~Node(){
        if(l) delete l; 
        if(r) delete r;
    }
} *root = 0;

int get_cnt(Node *p){
    if(!p) return 0;
    return p->cnt;
}

ll get_sum(Node *p){
    if(!p) return 0;
    return p->sum;
}

void upd(Node *p){
    p->cnt = 1 + get_cnt(p->l) + get_cnt(p->r);
    p->sum = p->key + get_sum(p->l) + get_sum(p->r);
}

Node *find(Node *p, int x){
    if(!p) return 0;
    if(p->key == x) 
        return p;
    if(p->key > x)
        return find(p->l, x);
    else
        return find(p->r, x);
}

Node *merge(Node *l, Node *r){
    if(!l) return r;
    if(!r) return l;
    if(l->prior > r->prior){
        l->r = merge(l->r, r);
        upd(l);
        return l;
    }
    else{
        r->l = merge(l, r->l);
        upd(r);
        return r;
    }
}  

pair<Node *, Node *> split(Node *p, int x){
    if(!p) return {0,0};
    if(p->key < x){
        auto [l,r] = split(p->r, x);
        p->r = l;
        upd(p);
        return {p,r};
    }
    else{
        auto [l,r] = split(p->l, x);
        p->l = r;
        upd(p);
        return {l,p};
    }
}  

Node *insert(Node *p, int x){
    if(find(p,x)) return p; //для уникальных ключей
    auto [l,r] = split(p, x);
    Node *m = new Node(x);
    return merge(l, merge(m, r)); 
}  

Node *erase(Node *p, int x){
    if(!find(p,x)) return p;
    auto [t,r] = split(p, x+1);
    auto [l,m] = split(t, x);    
    delete m;
    return merge(l,r); 
}

Node *find_kth(Node *p, int k){
    if(!p) return 0;    
    int cnt = get_cnt(p->l);
    if(k == cnt) 
        return p;
    else if(k < cnt) 
        return find_kth(p->l, k);
    else
        return find_kth(p->r, k-cnt-1);
}

ll get_sum(Node *p, int ql, int qr){
    auto [t,r] = split(p, qr);
    auto [l,m] = split(t, ql);
    ll res = get_sum(m);
    p = merge(l, merge(m,r));
    return res;
}

void print(Node *p){
    if(!p) return;
    print(p->l);
    cout << " " << p->key << " ";
    print(p->r);
}
