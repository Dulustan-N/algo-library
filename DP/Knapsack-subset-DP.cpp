/**
 * "0-1 knapsack with costs" problem:
 * n items with weights w[1]..w[n] and costs c[1]..c[n];
 * fit max cost of items into knapsack of weight capacity W.
 * b_c - cost of max cost mask found.
 * b_mask - max cost mask of items.
 * Complexity: time -> O(2^n n), space -> O(n).
*/

ll b_c=-1, b_mask=0;
for(int mask=0; mask<(1<<n); ++mask){
    ll curw=0, curc=0;
    for(int i=0; i<n; ++i)
        if((mask>>i)&1){
            curw += w[i];
            curc += c[i];                
        }
    if(curw > W) continue;
    if(curc > b_c){
        b_c = curc;
        b_mask = mask;
    }
}    

