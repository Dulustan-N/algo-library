/**
 * Suffix automaton (SA).
 * vector<Node> sa - the suffix automaton.
 * trie[v].go[x] - transition from v by 'a' + x.
 * trie[v].fin - v is terminal node (some suffix accepted in v).
 * trie[v].suf - suffix link from v.
 * trie[v].len - length of longest suffix accepted by v.
 * extend(c, sa, last) - extend SA from s to s+c, last - number of the current last node. 
 * finish(sa, last) - marks all terminal states of SA (do it only for complete SA).
 * Complexity: time -> O(n).
*/

struct Node{
    int len=0, suf=-1;
    map<char,int> go;
    int fpos = -1;
    bool fin=false;
};

void extend(char c, vector<Node> &sa, int &last){    
    int v = last;
    last = sa.size();
    sa.push_back({});
    sa[last].len = sa[v].len + 1;    
    sa[last].fpos = sa[last].len - 1;
    while(v!=-1 && !sa[v].go.count(c)){
        sa[v].go[c] = last;
        v = sa[v].suf;
    }
    if(v==-1){sa[last].suf = 0; return;}
    int u = sa[v].go[c];
    if(sa[u].len == sa[v].len + 1){
        sa[last].suf = u; return;
    }
    int u1=sa.size(); 
    sa.push_back({});
    sa[u1].len = sa[v].len + 1;
    sa[u1].suf = sa[u].suf;
    sa[u1].go = sa[u].go;
    sa[u1].fpos = sa[u].fpos;
    sa[last].suf = sa[u].suf = u1;
    while(v!=-1 && sa[v].go[c]==u){
        sa[v].go[c] = u1;
        v = sa[v].suf;
    } 
}
//Build SA
vector<Node> sa(1);
int last=0;
for(auto c : s){
    extend(c, sa, last);
}

//Mark final states
void finish(vector<Node> &sa, int &last){
    for(int v=last; v!=0; v=sa[v].suf)
        sa[v].fin = true;
}


/**
 * Few common uses of Suffix Automaton.
*/

//Count number of occurences of each substring in s
vector<int> cnt(sa.size(),-1);
auto dfs = [&](int v, auto&& dfs)->int{        
    if(cnt[v]!=-1) return cnt[v];        
    cnt[v] = sa[v].fin ? 1 : 0;
    for(auto [c,u] : sa[v].go)
        cnt[v] += dfs(u, dfs);
    return cnt[v];
};    
dfs(0, dfs);

//Number of distinct substrings of s
vector<ll> dp(sa.size());
auto dfs = [&](int v, auto&& dfs)->ll{        
    if(dp[v]) return dp[v];        
    dp[v] = 1;
    for(auto [c,u] : sa[v].go)
        dp[v] += dfs(u, dfs);
    return dp[v];
};    
cout << dfs(0, dfs)-1 << endl;   

//K-th lexicographically smallest DISTINCT string
vector<ll> dp(sa.size(),-1);
auto dfs = [&](int v, auto&& dfs)->ll{        
    if(dp[v]!=-1) return dp[v];        
    dp[v] = 1;
    for(auto [c,u] : sa[v].go)
        dp[v] += dfs(u, dfs);
    return dp[v];
};    
for(int v=0; v<sa.size(); ++v)
    if(dp[v]==-1)
        dfs(v, dfs);
        
if(dp[0]-1 < k){
    cout << "NO\n"; return;
}
int v=0;
string ans; 
bool ok=true;   
while(ok){ 
    if(k==0) break;       
    for(auto [c,u] : sa[v].go){    
        if(k==0){ok=false; break;}
        if(dp[u]<k)
            k -= dp[u];            
        else{
            ans.push_back(c);
            --k;
            v = u;
            break; 
        }
    }
}
cout << ans << endl;


