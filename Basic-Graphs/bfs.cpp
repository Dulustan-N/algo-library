/**
 * BFS algorithm.
 * vertices: 1..n.
 * Complexity: time -> O(n+m).
*/

int n, m;
vector<vector<int>> g(n+1);

vector<bool> used(n+1);
deque<int> q;
q.push_back(v0);
used[v0] = true;           
while(q.size()){
    int v = q.front(); q.pop_front();
    for(auto u : g[v]){
        if(!used[u]){
            used[u] = true;
            q.push_back(u);                
        }
    }
}

