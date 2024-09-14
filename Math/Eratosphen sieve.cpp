/**
 * Eratosphen sieve algorithm.
 * to compute all prime numbers from 1 to N.
 * Complexity: time -> O(N log log N), space -> O(N).
*/

const int N = 1e6;
vector<bool> prime(N+1,true);
vector<int> primes;

for(int x=2; x*x<=N; ++x){
    if(!prime[x]) continue;
    for(int y=x*x; y<=N; y+=x)
        prime[y] = false;
}
for(int x=2; x<=N; ++x)
    if(prime[x])
        primes.push_back(x);


