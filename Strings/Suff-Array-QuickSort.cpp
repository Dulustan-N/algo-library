/**
 * Suffix Array building by using Quick Sort.
 * Complexity: time -> O(n log^2).
*/

void SuffArray(string s, vector<int>& p, vector<int> &c){
    s.push_back('$');
    int n = s.size();
    p.resize(n); c.resize(n);
    for(int k=0; k<n; k = (k ? k*2 : 1)){
        vector<pair<pair<int,int>,int>> t(n);
        for(int i=0; i<n; ++i)
            if(k==0) t[i] = {{s[i],0},i};
            else t[i] = {{c[i], c[(i+k)%n]}, i};            
        sort(t.begin(), t.end());
        int cur=-1;
        for(int i=0; i<n; ++i){
            p[i] = t[i].second;
            if(i==0 || t[i].first != t[i-1].first)
                ++cur;
            c[p[i]] = cur;
        }
        if(cur == n-1) break;
    }
}

void lcp_build(string s, vector<int> &p, vector<int> &c, vector<int> &lcp){
    int n = s.size();
    lcp.resize(n-1);
    int k=0;
    for(int i=0; i<n; ++i){
        if(c[i] == n-1) continue;
        while(max(i,p[c[i]+1])+k<n && s[i+k]==s[p[c[i]+1]+k])
            ++k;
        lcp[c[i]] = k;
        k = max(k-1, 0);
    }    
}
