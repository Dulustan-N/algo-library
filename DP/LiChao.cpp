/**
 * Li Chao tree (DP optimization) - implemented Li Chao Tree class.
 * Line is k * x + b.
 * LiChao - is convex hull (CHT) f(x) = min_i (k_i * x + b_i).
 * get(0, 0, n, x) - value of CHT at x.
 * upd(0, 0, n, line) - add new line to CHT.
 * 1d DP transtion form: dp[i] = min_{j<i} a[i]*b[j] + dp[j],
 * 1 <= i <= n.
 * 2d DP transtion form: dp[t][i] = min_{j<i} a[i]*b[j] + dp[t-1][j],
 * 1 <= t <= k, 1 <= i <= n.
 * Complexity: upd -> O(log n), get -> O(log n).
*/

struct LiChao{    
    struct Line{
        ll k,b;
        Line(ll k, ll b) : k(k), b(b){}
        auto get(ll x){return k * x + b;}
    };
    vector<Line> t;
    int n;
    const Line NONE = {0, INF_LL};
    LiChao(int n) : n(n){t.resize(4*n, NONE);}
    void upd(int p, int l, int r, Line line){
        if(line.k == t[p].k){
            if(line.b < t[p].b) 
                t[p] = line;
            return;
        }
        if(r-l==1){
            if(line.get(l) < t[p].get(l)) 
                t[p] = line;
            return; 
        }
        int m=(l+r)/2;
        if(line.get(m) < t[p].get(m))
            swap(line, t[p]);
        if(line.k > t[p].k)
            upd(2*p+1, l, m, line);
        else
            upd(2*p+2, m, r, line);
    }
    ll get(int p, int l, int r, int q){
        if(r-l==1) return t[p].get(q);
        int m=(l+r)/2;
        if(q<m) 
            return min(t[p].get(q), get(2*p+1, l, m, q));
        else
            return min(t[p].get(q), get(2*p+2, m, r, q));
    }
    void upd(ll k, ll x){
        return upd(0, 0, n, Line(k,x));
    }
    ll get(int q){
        return get(0, 0, n, q);
    }    
};