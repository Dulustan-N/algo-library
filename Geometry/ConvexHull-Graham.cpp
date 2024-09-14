/**
 * Convex hull - Graham's algorithm
 * convex_hull(p): p is vector of points, 
 *      returns the convex hull (anticlockwise direction).
 * Complexity: time -> O(n log n), space -> O(n). 
 */

vector<Vec> convex_hull(vector<Vec> p){
    int n=p.size();
    if(n<=2) return p;
    Vec p0 = p[0];
    for(auto v : p)
        if(v.y<p0.y || (v.y==p0.y && v.x<p0.x))
            p0 = v;
    auto cmp = [&](Vec v, Vec u)->bool{
        Vec a=v-p0, b=u-p0;
        return cross(a,b)>0 || (cross(a,b)==0 && len2(a)<len2(b));
    };
    sort(p.begin(), p.end(), cmp); 
    vector<Vec> hull;
    for(int i=0; i<n; ++i){
        while(hull.size()>=2){
            auto p0=hull[hull.size()-2], p1=hull.back();
            if(cross(p1-p0, p[i]-p1)<=0)
                hull.pop_back();
            else
                break;
        }
        hull.push_back(p[i]);
    }
    return hull;
}
