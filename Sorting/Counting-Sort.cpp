/**
 * Counting Sort.
 * This assumes that 0 <= a[i] < M.
 * Complexity: time -> O(n+M).
*/

void counting_sort(vector<int>& a, int M){
    int n = a.size(); 
    vector<int> cnt(M), pos(M);
    for(auto i : a)
        ++cnt[i];    
    for(int i=1; i<M; ++i)
        pos[i] = pos[i-1] + cnt[i-1];
    vector<int> b(n);
    for(auto i : a){
        b[pos[i]] = i;
        ++pos[i];
    }
    a = b;
}
