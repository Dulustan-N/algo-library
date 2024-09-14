/**
 * Treap (Cartesian tree) with implicit key.
 * key is implicit and equal to a number of nodes to the left (position of the node).
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

struct Node{
    int val, prior, cnt=1;    
    ll sum; int min;
    int add=0;
    bool rev=0;
    Node *l=0, *r=0;
    Node(int _val) : val(_val){
        prior = rnd();
        sum = _val;
        min = _val;
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
int get_min(Node *p){
    if(!p) return INF;
    return p->min;
}
void upd(Node *p){
    p->cnt = 1 + get_cnt(p->l) + get_cnt(p->r);
    p->sum = p->val + get_sum(p->l) + get_sum(p->r);
    p->min = min(p->val, min(get_min(p->l), get_min(p->r)));
}

void add(Node *p, int v){
    if(!p) return;
    p->add += v;
    p->min += v;
    p->sum += v * 1ll * (p->cnt);
    p->val += v;
}
void push(Node *p){
    if(p->add){
        add(p->l, p->add);
        add(p->r, p->add);  
        p->add = 0;
    }     
    if(p->rev){
        swap(p->l, p->r);
        if(p->l) p->l->rev ^= 1;
        if(p->r) p->r->rev ^= 1;
        p->rev = 0;
    }
}

Node *merge(Node *l, Node *r){
    if(!l) return r;
    if(!r) return l;
     
    if(l->prior > r->prior){
        push(l);
        l->r = merge(l->r, r);
        upd(l);
        return l;
    }
    else{
        push(r);
        r->l = merge(l, r->l);
        upd(r);
        return r;
    }
}  
pair<Node *, Node *> split(Node *p, int x){
    if(!p) return {0,0};
    push(p);
    int cnt = get_cnt(p->l);
    if(x > cnt){
        auto [l,r] = split(p->r, x-cnt-1);
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

Node *insert(Node *p, int x, int v){
    auto [l,r] = split(p, x);
    Node *m = new Node(v);    
    return merge(l, merge(m, r)); 
}  
Node *erase(Node *p, int x){
    if(get_cnt(p)<=x) return 0; 
    auto [t,r] = split(p, x+1);
    auto [l,m] = split(t, x);
    delete m;
    return merge(l,r); 
}
Node *get(Node *p, int k){
    if(!p) return 0;    
    push(p);
    int cnt = get_cnt(p->l);
    if(k == cnt) 
        return p;
    else if(k < cnt) 
        return get(p->l, k);
    else
        return get(p->r, k-cnt-1);
}

ll get_sum(Node *p, int ql, int qr){
    auto [t,r] = split(p, qr);
    auto [l,m] = split(t, ql);
    ll res = get_sum(m);
    p = merge(l, merge(m,r));
    return res;
}

ll get_min(Node *p, int ql, int qr){
    auto [t,r] = split(p, qr);
    auto [l,m] = split(t, ql);
    ll res = get_min(m);
    p = merge(l, merge(m,r));
    return res;
}

void add(Node *p, int ql, int qr, int v){
    auto [t,r] = split(p, qr); 
    auto [l,m] = split(t, ql); 
    add(m, v);
    p = merge(l, merge(m,r));
}

void reverse(Node *p, int ql, int qr){
    auto [t,r] = split(p, qr); 
    auto [l,m] = split(t, ql); 
    m->rev ^= 1;
    p = merge(l, merge(m,r));
}

void print(Node *p){
    if(!p) return;
    push(p);
    print(p->l);
    cout << " " << p->val << " ";
    print(p->r);
}
