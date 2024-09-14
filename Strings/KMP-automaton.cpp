/**
 * KMP automaton:
 * kmp[i][c] = transition from s[i] to s[kmp[i][c]] by symbol c.
*/

const int K=26;
s.push_back('$');    
int n = s.size();
vector<int> pi(n); 
for(int i=1; i<n; ++i){
    int j = pi[i-1];
    while(j>0 && s[j]!=s[i])
        j = pi[j-1];
    if(s[i]==s[j])
        ++j;
    pi[i] = j;
}    
vector<vector<int>> kmp(n,vector<int>(K));
for(int i=0; i<n; ++i){
    for(int c=0; c<K; ++c){
        if(i>0 && s[i]!='a'+c)
            kmp[i][c] = kmp[pi[i-1]][c];
        else
            kmp[i][c] = i + (s[i] == 'a'+c);
    }
}