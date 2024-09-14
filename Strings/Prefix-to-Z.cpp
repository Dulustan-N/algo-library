/**
 * Transform Z-function to prefix-function.
 * Transform prefix-function to Z-function.
 * Restore string by its prefix-function.
*/

// Z-function to prefix-function
vector<int> pi(n);
for(int i=1; i<n; ++i)
    pi[i+z[i]-1] = max(pi[i+z[i]-1], z[i]);    
for(int i=n-1; i>0; --i)
    pi[i] = max(pi[i], pi[i+1]-1);

// Prefix-function to z-function
vector<int> z(n); 
z[0] = n;
for(int i=1; i<n; ++i)
    if(pi[i])
        z[i-pi[i]+1] = pi[i];

int i=1;
while(i<n){
    int j;
    for(j=1; j<z[i] && z[j]>=z[i+j]; ++j){
        z[i+j] = min(z[i]-j, z[j]);
    }
    i += j;
}

// Prefix-function to string
string prefix_to_string(const vector<int> &pi, int &cnt){
    int n =pi.size();
    string s(n,0);
    cnt=1;
    for(int i=1; i<n; ++i){
        if(pi[i]){
            s[i] = s[pi[i]-1];
        }
        else{
            vector<bool> used(cnt);
            for(int j=pi[i-1]; j>0; j=pi[j-1])
                used[s[j]-'a'] = 1;
            for(int c=1; c<cnt && !s[i]; ++c)
                if(!used[c])
                    s[i] = 'a'+c;
            if(!s[i]){                
                s[i] = 'a'+cnt;
                ++cnt;
            }
        }
    }
    return s;
}
