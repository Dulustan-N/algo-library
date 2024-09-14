/**
 * Pick's Theorem to find number of points inside polygon.
 * Let P is polygon with all vertices in integer coordinates.
 * I - number of points inside P, 
 * B - number of points on the boundary of P.
 * Pick's Theorem: S = I + B/2 - 1.
 */

ll area2(const vector<Vec> &p){
    int n = p.size();
    ll res=0;
    for(int i=0; i<n; ++i){
        res += cross(p[i], p[i<n-1 ? i+1 : 0]);
    }
    return abs(res);
}

void lattice_points(const vector<Vec> &p, ll &B, ll &I){
    int n = p.size();
    B = 0;
    for(int i=0; i<n; ++i){
        int j = i<n-1 ? i+1 : 0;        
        B += abs(gcd(p[j].x - p[i].x, p[j].y - p[i].y));
    }
    ll S2 = area2(p);
    I = (S2 - B) / 2 + 1;
};