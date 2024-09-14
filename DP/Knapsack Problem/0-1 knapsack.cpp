/**
 * "0-1 knapsack" problem:
 * n items with weights w[1]..w[n];
 * fit max weight of items into knapsack of weight capacity W.
 * dp[i][x] - capacity x can be filled using only items 1..i (i may be hidden parameter).
 * pick[i][x] - item i is picked in dp[i][x].
 * Complexity: time -> O(nW), space -> O(W) / O(nW).
*/

// O(W) memory, no answer recovery.
vector<bool> dp(W+1);    
dp[0] = 1;
for(int i=1; i<=n; ++i)
    for(int x=W; x>=w[i]; --x)
        dp[x] = dp[x] | dp[x-w[i]];
int ans = W;
while(!dp[ans])
    --ans;

// O(nW) memory with answer recovery
vector<vector<bool>> dp(n+1, vector<bool>(W+1));    
vector<vector<bool>> pick(n+1, vector<bool>(W+1));
dp[0][0] = 1;
for(int i=1; i<=n; ++i){
    for(int x=0; x<=W; ++x){        
        dp[i][x] = dp[i-1][x];
        pick[i][x] = 0;
        if(x>=w[i] && dp[i-1][x-w[i]] && !dp[i][x]){
            dp[i][x] = 1;
            pick[i][x] = 1;
        }
    }
}

vector<int> ans;
int x=W;
while(!dp[n][x])
    --x; 
for(int i=n; i>0; --i){
    if(pick[i][x]){
        ans.push_back(i);
        x -= w[i];
    }
}
reverse(ans.begin(), ans.end());


//answer recovery without choice memory
vector<int> ans;
int x=W;
while(x>0 && !dp[n][x])
    --x; 
for(int i=n; i>0; --i){
    if(dp[i][x] != dp[i-1][x]){
        ans.push_back(i);
        x -= w[i];
    }
}
reverse(ans.begin(), ans.end());


