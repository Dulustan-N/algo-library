/**
 * Euler totient function computation.
 * Complexity: time -> O(sqrt(n)).
*/

int phi(int n){
    int res=n;
    for(int i=2; i*i<=n; ++i){
        if(n%i==0){
            while(n%i==0)
                n /= i;
            res -= res/i;
        }
    }
    if(n>1) res -= res/n;
    return res;
}


/**
 * Euler function computatation for 1 to n.
 * Complexity: time -> O(n log log n).
*/

vector<int> phi(n+1);
iota(phi.begin(), phi.end(), 0);
for(int x=2; x<=n; ++x){
    if(phi[x] == x){
        for(int y=x; y<=n; y+=x)
            phi[y] -= phi[y] / x;
    }
}