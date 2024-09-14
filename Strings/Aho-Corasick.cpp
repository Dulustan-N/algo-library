/**
 * Aho-Corasick (AC) automaton to find patterns s_1,...,s_k (total length m)
 * in a text t of length n.
 * vector<Node> trie - trie on which AC is built.
 * trie[v].go[x] - transition from v by 'a' + x.
 * trie[v].fin - v is terminal node (some pattern is recognized).
 * trie[v].fins - list of patterns recognized at node v.
 * trie[v].ins - list of nodes from which we can get to v only by outlinks. 
 * trie[v].suf - suffix link from v.
 * trie[v].out - outlink from v.
 * add(s, i, t) - adding pattern s (number i) to trie t.
 * init(t) - build AC automaton on a trie t by BFS in O(m).
 * Complexity: time -> O(m + n + z), where z - total number of pattern appearances in text.
*/

const int K=26;
struct Node{
    array<int,K> go;
    bool fin=false;
    vector<int> fins, ins;
    int suf=0, out=0;
    Node(){go.fill(-1);}
};

void add(const string &s, int i, vector<Node> &t){
    int v=0;
    for(auto c : s){
        if(t[v].go[c-'a']==-1){
            t[v].go[c-'a'] = t.size();
            t.emplace_back();
        }
        v = t[v].go[c-'a'];
    }
    t[v].fin = true;
    t[v].fins.push_back(i);
}

void init(vector<Node> &t){
    deque<int> q;
    for(int x=0; x<K; ++x){
        int u = t[0].go[x];
        if(u!=-1){
            t[0].ins.push_back(u);
            q.push_back(u);
        }
        else
            t[0].go[x] = 0;
    }
    while(q.size()){
        int v=q.front(); q.pop_front();
        for(int x=0; x<K; ++x){
            int u = t[v].go[x];
            if(u!=-1){
                t[u].suf = t[t[v].suf].go[x];   
                if(t[t[u].suf].fin)
                    t[u].out = t[u].suf;
                else
                    t[u].out = t[t[u].suf].out;
                t[t[u].out].ins.push_back(u);
                q.push_back(u);                  
            }
            else 
                t[v].go[x] = t[t[v].suf].go[x]; 
        }
    }
}

vector<Node> trie(1);