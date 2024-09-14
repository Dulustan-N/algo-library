/**
 * Scanline algorithm example.
 * Problem: n segments on a line. Find point covered 
 * by maximal number of segments.
 * Complexity: time -> O(N log log N).
*/

int n; cin >> n;
vector<pair<int,int>> event(2*n);
for(int i=0; i<n; ++i){
    int l,r; cin >> l >> r;
    event[2*i] = {l, 1};
    event[2*i+1] = {r, -1};
}
sort(event.begin(), event.end(), [](pii &a, pii &b){
    return a.F<b.F || (a.F==b.F && a.S>b.S);
});
int bal=0, best=-1, ans=-1; 
for(auto [x,t] : event){
    bal += t;
    if(bal>best){
        best = bal;
        ans = x;
    }        
}
cout << ans << " " << best << endl;    



