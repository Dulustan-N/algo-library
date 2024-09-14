/**
 * Convex Hull Trick (CHT) DP Optimization - implemented CHT class.
 * Line is k * x + b;
 * Line.xb - intersection of line with previous line of CHT.
 * hull - is convex hull (CHT) f(x) = min_i (k_i * x + b_i).
 * get(x) - value of CHT at x, deleting all lines to the left.
 * add(k, b) - add new k * x + b line to CHT.
 * 1d DP transtion form: dp[i] = min_{j<i} a[i]*b[j] + dp[j],
 * 1 <= i <= n.
 * 2d DP transtion form: dp[t][i] = min_{j<i} a[i]*b[j] + dp[t-1][j],
 * 1 <= t <= k, 1 <= i <= n.
 * Condition: b[j] decreasing, a[i] increasing.
 * Complexity: 1d DP -> O(n log n), 2d DP -> O(kn log n).
*/

struct CHT{
    struct Line{
        ll k,b,xb=0;
        Line(ll k, ll b, ll xb=0) : k(k), b(b), xb(xb) {}
        auto get(ll x){return k * x + b;}
        ll cross(Line oth){
            ll x = (oth.b - b) / (k - oth.k);
            return x>=0 ? x: x-1; 
        };
    };
    deque<Line> hull; 
    auto get(ll x){
        while(hull.size()>1 && hull[0].get(x) >= hull[1].get(x))
            hull.pop_front();
        return hull[0].get(x);
    }
    auto add(ll k, ll b){
        if(hull.size() && hull.back().k == k){
            if(hull.back().b < b) return;
            hull.pop_back();
        }
        Line line(k,b);
        while(hull.size()>1 && line.cross(hull.back()) <= hull.back().xb)            
            hull.pop_back();        
        if(hull.size()) line.xb = line.cross(hull.back());
        else line.xb = -INF_LL;
        hull.push_back(line);
    }    
};