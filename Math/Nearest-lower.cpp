/**
 * Algorithm to find nearest lower/higher numbers
 * in a[1]...a[n].
 * llo[i] = index of nearest on the left lower number.
 * lhi[i] = index of nearest on the left higher number.
 * rlo[i] = index of nearest on the right lower number.
 * rhi[i] = index of nearest on the right higher number.
 * Complexity: time -> O(n).
*/

vector<int> llo(n+1, 0), lhi(n+1, 0);    
vector<int> rlo(n+1, n+1), rhi(n+1, n+1);
{
    stack<int> st1, st2;
    for(int i=1; i<=n; ++i){
        while(st1.size() && a[st1.top()] > a[i]){
            rlo[st1.top()] = i;
            st1.pop();
        }
        if(st1.size()) llo[i] = st1.top();
        st1.push(i);
        while(st2.size() && a[st2.top()] < a[i]){
            rhi[st2.top()] = i;
            st2.pop();
        }
        if(st2.size()) lhi[i] = st2.top();
        st2.push(i);
    }  
}