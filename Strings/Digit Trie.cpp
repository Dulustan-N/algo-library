/**
 * Digit Trie.
 * Node: go[x] - transition by x = 0 or 1.
 *       fin - terminal state.
 *       cnt - number of strings going through the node.
 * add(x, t) - add number x to the trie t in O(log x)).
 * check(x, t) - check if number x is in the trie t in O(log x).
*/

struct Node{
    array<int,2> go{{}};
    bool fin=false;
    int cnt=0;
    Node(){go.fill(-1);}
};

void add(int x, vector<Node> &t){
    int v=0;
    for(int i=30; i>=0; --i){
        int c = (x>>i) & 1;
        if(t[v].go[c]==-1){
            t.push_back({});
            t[v].go[c] = t.size()-1;
        }                     
        v = t[v].go[c];  
        ++t[v].cnt;             
    }
    t[v].fin = true;    
}    

bool check(int x, const vector<Node> &t){
    int v=0;
    for(int i=30; i>=0; --i){
        int c = (x>>i) & 1;            
        v = t[v].go[c];
        if(v==-1) return false;
    }
    return t[v].fin;
}

