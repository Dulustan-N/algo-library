#include<bits/stdc++.h>
using namespace std;

using ll = long long; using ld = long double; 
using pii = pair<int,int>; using pll = pair<ll,ll>;
using vi = vector<int>; using vl = vector<ll>; using vc = vector<char>; using vb = vector<bool>;
const int INF = 1e9+10; const ll INF_LL = 2e18; const ld PI = atan2(0,-1);
#define F first
#define S second
#define all(x) (x).begin(), (x).end()
#define forn(i,a,b) for(auto i=a; i!=b; ++i)
#define forr(i,a,b) for(auto i=a; i!=b; --i)


int main(int argc, char* argv[]){
    mt19937_64 gen(atoi(argv[1]));
    auto rnd = [&gen](ll a, ll b)->ll{
        return a + gen()%(b-a+1);
    };

    
}