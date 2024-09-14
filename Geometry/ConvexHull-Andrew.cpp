/**
 * Convex hull - Andrew's algorithm.
 * convex_hull(p): p is vector of points, 
 *      returns the convex hull (anticlockwise direction).
 * This returns ALL the points of p on the convex hull.
 * Complexity: time -> O(n log n), space -> O(n). 
 */

vector<Vec> convex_hull(vector<Vec> p){
    int n=p.size();
    if(n<=2) return p;
    sort(p.begin(), p.end(), [](Vec a, Vec b){
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }); 
    vector<Vec> hull;
    for(int t=0, sz=0; t<2; ++t){
        for(int i=0; i<n; ++i){
            while(hull.size()-sz >= 2){
                auto p0=hull[hull.size()-2], p1=hull.back();
                if(cross(p1-p0, p[i]-p1)<0)
                    hull.pop_back();
                else
                    break;
            }
            hull.push_back(p[i]);
        }  
        hull.pop_back();
        sz = hull.size();
        reverse(p.begin(), p.end());
    }
    return hull;
}