/**
 * Trie structure.
 * Node: go[x] - transition by symbol 'a'+x.
 *       fin - terminal state.
 *       cnt - number of strings going through the node.
 * add(s, t) - add string s to the trie t -> O(len(s)).
 * check(s, t) - check if string s is in the trie t -> O(len(s)).
 * get_kth(k, t) - find kth lexicographically smallest string in the trie t -> O(n).
 * Builds in O(n), where n is a length of string s.
 * 
*/

const int K=26;
struct Node{
    array<int,K> go;
    bool fin=false;
    int cnt=0;
    Node(){go.fill(-1);}
};

void add(const string &s, vector<Node> &t){
    int v=0;
    for(auto c : s){
        if(t[v].go[c-'a']==-1){
            t[v].go[c-'a'] = t.size();
            t.emplace_back();
        }
        v = t[v].go[c-'a'];
        ++t[v].cnt;
    }
    t[v].fin = true;
}
bool check(const string &s, const vector<Node> &t){
    int v=0;
    for(auto c : s){
        v = t[v].go[c-'a'];
        if(v==-1) return false;
    }
    return t[v].fin;
}

string get_kth(int k, const vector<Node> &t){
    int v=0;       
    string res;
    while(k){
        for(int x=0; x<K; ++x){
            int u = t[v].go[x];
            if(u == -1) continue;                
            if(t[u].cnt < k)
                k -= t[u].cnt;
            else{
                res.push_back('a'+x);
                v = u;
                if(t[v].fin) --k;
                break;
            }
        }                
    }
    return res;
}
