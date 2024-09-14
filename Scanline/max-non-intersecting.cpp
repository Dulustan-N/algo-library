/**
 * Problem: n segments on a line. Find  maximal 
 * non-intersecting set of segments.
 * Complexity: time -> O(n log n).
*/

int n; cin >> n;
vector<pair<int,int>> seg(n);
for(int i=0; i<n; ++i){cin >> seg[i].F >> seg[i].S;}
sort(seg.begin(), seg.end(), [](pii &a, pii &b){
    return a.S<b.S;
});
int cnt=0, cur=-INF; 
for(auto x : seg){
    if(x.F >= cur){
        ++cnt;
        cur = x.S;
    }
}


