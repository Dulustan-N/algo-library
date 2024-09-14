/**
 * Algorithm to find a min in a sliding window.
 * ans[i] = min(a[i-k+1]..a[i]).
 * Complexity: time -> O(n).
*/

deque<int> q;
for(int i=1; i<=n; ++i){
    if(i>k && q.front()==i-k)
        q.pop_front();
    while(q.size() && a[q.back()]>=a[i])
        q.pop_back();
    q.push_back(i);
    if(i>=k)
        ans.push_back(d.front());
}    