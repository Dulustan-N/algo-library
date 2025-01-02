/**
 * Classical string function for a string s of size n.
 * Prefix function pi[i] = max {k | k <= i, s[0..k-1] = s[i-k+1..i-1]} for i>0, pi[0] = 0.
 * Z-function z[i] = max {k | k <= i, s[0..k-1] = s[i..i+k-1]} for i>0, z[0] = 0. 
 * Complexity: time -> O(n).
*/

//Prefix function
vector<int> pi(n); 
{
    for(int i=1; i<n; ++i){
        int j = pi[i-1];
        while(j>0 && s[j]!=s[i])
            j = pi[j-1];
        if(s[i]==s[j])
            ++j;
        pi[i] = j;
    }
}

//Z function
vector<int> z(n); 
{
    z[0] = n;
    int l=0, r=0; //[l,r)
    for(int i=1; i<n; ++i){
        if(i < r) z[i] = min(z[i-l], r-i);
        while(i+z[i] < n && s[i+z[i]] == s[z[i]])
            ++z[i];
        if(i+z[i] > r)
            l = i, r = i+z[i];
    }
}

