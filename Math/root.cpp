/**
 * Find x^(1/p) rounded down.
 * root(x, p) --- x ^ (1/p).
 * ok(y, p, x) --- check that y^p <= x.
*/

bool ok(ll y, int p, ll x){
    for(int i=0; i<p; ++i)
        x /= y;
    return x > 0;
}
ll root(ll x, int p){
    ll y = pow(x, 1./p);
    while(ok(y, p, x)) ++y;
    while(!ok(y, p, x)) --y;
    return y;
}

// safe pow
ll spow(ll x, int k){
    ll res = 1;
    for(; k; k >>= 1, x = x * x)
        if(k & 1) res *= x;
    return res;
}
