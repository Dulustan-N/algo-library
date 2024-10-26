/**
 * Manacher's algorithm to find all palindromes in a string
 * s of size n.
 * d.size() = 2*n
 * s[l..r] - palindrome if and only if d[l+r] >= r-l+1.
 * Complexity: time -> O(n).
*/

vector<int> manacher(const string &s0){
    string s;
    for(int i=0; i<(int)s0.size(); ++i){
        s.push_back(s0[i]);
        s.push_back('#');
    }
    int n=s.size();
    vector<int> d(n, 1);
    int l=0, r=0;
    for(int i=1; i<n; ++i){
        if(i<r)
            d[i] = min(r-i+1, d[l+r-i]);
        while(i-d[i]>=0 && i+d[i]<n && s[i-d[i]]==s[i+d[i]])
            ++d[i];
        if(i+d[i]-1>r)
            l = i-d[i]+1, r = i+d[i]-1;
    }
    return d;
}

