/**
 * Factorization of a number.
 * Complexity: time -> O(sqrt(n)).
*/


// using map
map<ll,int> p;
for(ll d=2; d*d<=n; ++d){
    while(n%d == 0){
        ++p[d];
        n /= d;
    }
}
if(n>1) ++p[n];


// using vector<pair>
vector<pair<ll,int>> p;
for(ll d=2; d*d<=n; ++d){
    if(n%d != 0) continue;
    p.push_back({d,0});
    while(n%d==0){
        ++p.back().second;
        n /= d;
    }
}
if(n>1) p.push_back({n,1});