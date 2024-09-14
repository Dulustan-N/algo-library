/**
 * Problem: n segments on a line and a segment. 
 * Find minimal cover of the segment.
 * Complexity: time -> O(n log n).
*/

//find minimal cover of a segment
int L; cin >> L;
int n; cin >> n;
vector<pair<int,int>> seg(n);
for(int i=0; i<n; ++i){cin >> seg[i].F >> seg[i].S;}
sort(seg.begin(), seg.end());
int cnt=0, cur=0, best=-1; 
for(auto x : seg){
    if(x.F > cur){
        if(best==-1) break;
        cur = best;    
        ++cnt;
    }
    else{
        best = max(best, x.S);
    }
}
cout << cnt << endl;

