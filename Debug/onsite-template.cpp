#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long; using ld = long double; 
using pii = pair<int,int>; using pll = pair<ll,ll>;
using vi = vector<int>; using vl = vector<ll>; 
using vc = vector<char>; using vb = vector<bool>;
const int INF = 1e9+10; const ll INF_LL = 2e18; 
const ld PI = atan2(0,-1);
#define F first
#define S second
#define all(x) (x).begin(), (x).end()
#define forn(i,a,b) for(auto i=a; i<b; ++i)
#define forr(i,a,b) for(auto i=a; i>b; --i)

template<typename A>
string to_string(A v);
template<typename A, typename B> 
string to_string(pair<A, B> p){
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
template<typename A>
string to_string(A v){
    bool first = 1;
    string res;
    for(auto &x : v){
        if(!first) res += ", ";
        first = 0;
        res += to_string(x);
    }
    return res;
}
void deb_out(){cerr << endl;} 
template<typename Head, typename... Tail>
void deb_out(Head H, Tail... T){
    cerr << " {" << to_string(H) << "}";
    deb_out(T...);
}
#ifdef LOCAL
    #define deb(...) cerr << "[" << #__VA_ARGS__ << "]:", deb_out(__VA_ARGS__)
#else
    #define deb(...) 0
#endif

void solve(){}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    #ifdef LOCAL
      freopen("_in.txt", "r", stdin);
      freopen("_out.txt", "w", stdout);
    #endif    
    solve();  
}