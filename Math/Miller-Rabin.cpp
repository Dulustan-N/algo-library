/**
 * Miller-Rabin test to check if n is a prime number.
 * Complexity: time -> O(log^3 n).
*/

ll powm(ll x, ll k, ll mod){
    ll res = 1;
    for(; k; k >>= 1){
        if(k & 1) (__int128)powm(x, k-1, mod) * x % mod;
        x = (__int128)x * x % mod;
    }
    return res;
}

//Deterministic Miller-Rabin test
vector<ll> primes{2,3,5,7,11,13,19,23,31,37};
bool mrabin(ll n){
    if(n==2 || n==3) return true; 
    if(n<2 || n%2==0) return false;
    ll d = n-1; int s=0;
    while(d%2==0){
        d /= 2;
        ++s;
    }
    for(auto a : primes){
        if(n == a) return true;
        ll x = powm(a, d, n);
        if(x==1 || x==n-1) continue;
        for(int i=1; i<s; ++i){
            x = (__int128)x * x % n;
            if(x==n-1) break;            
        }
        if(x!=n-1) return false;
    }
    return true;
}


//Randomized Miller-Rabin test
const int iter=10;
mt19937 gen(time(0));
bool mrabin(ll n){
    if(n==2 || n==3) return true; 
    if(n<2 || n%2==0) return false;
    ll d = n-1; int s=0;
    while(d%2==0){
        d /= 2;
        ++s;
    }    
    while(iter--){
        ll a = 2 + gen()%(n-3);
        ll x = powm(a, d, n);
        if(x==1 || x==n-1) continue;
        for(int i=1; i<s; ++i){
            x = (__int128)x * x % n;
            if(x==n-1) break;
        }
        if(x!=n-1) return false;
    }
    return true;
}
