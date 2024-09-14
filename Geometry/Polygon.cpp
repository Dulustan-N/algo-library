/**
 * Some Polygon algorithms.
 * p = {p[0],..,p[n-1]} - polygon in anticlockwise order.
 * inside3(p, a, b, c) - check if p is inside triangle abc -> O(1).
 * inside(q, p) - check if p is inside ANY polygon p -> O(n).
 * inside_convex(q, p) - check if p is inside CONVEX polygon p -> O(log n).
 * area2(p) - double area of ANY polygon -> O(n).
 */

//check if point inside CONVEX polygon
bool in_angle(Vec p, Vec o, Vec a, Vec b){
    return sgn(cross(a-o,p-o)) * sgn(cross(a-o,b-o)) >= 0
        && sgn(cross(b-o,p-o)) * sgn(cross(b-o,a-o)) >= 0; 
}
bool inside3(Vec p, Vec a, Vec b, Vec c){
    return in_angle(p,a,b,c) && in_angle(p,b,c,a);
}
bool inside_convex(Vec q, vector<Vec> &p){
    int n = p.size();
    if(!in_angle(q, p[0], p[1], p[n-1])) 
        return false;
    auto cmp = [&](Vec v, Vec u)->bool{
        Vec a=v-p[0], b=u-p[0];
        return cross(a,b)>0 || (cross(a,b)==0 && len2(a)<len2(b));
    };
    int j = lower_bound(p.begin()+1, p.end(), q, cmp) - p.begin();    
    return inside3(q, p[0], p[j-1], p[j]);
}

//check if point inside ANY polygon
bool inside(Vec q, vector<Vec> &p){
    double total = 0;
    int n = p.size();
    for(int i=0; i<n; ++i){
        Vec a = p[i]-q, b = p[(i+1)%n]-q;
        if(cross(a, b)==0 && dot(a, b)<=0)
            return true;
        total += angle(a, b); 
    }
    total = abs(total);
    return (abs(total-2*PI) < 1);
}

//Double area of ANY polygon
ll area2(const vector<Vec> &p){
    int n = p.size();
    ll res=0;
    for(int i=0; i<n; ++i){
        res += cross(p[i], p[i<n-1 ? i+1 : 0]);
    }
    return abs(res);
}