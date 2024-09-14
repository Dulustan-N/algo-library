/**
 * struct for 2d vectors and points, and related functions.
 * Can add and subtract vectors, multiply/divide by scalar.
 * dot(a, b) - dot product of a and b.
 * cross(a, b) - cross product of a and b.
 * len2(a) - sqaured length of a.
 * angle(a, b) - oriented angle from a to b.
 * top(a) - a is in upper halfplane.
 * cmp(a) - comparator to sort vectors by angle.
 * in_angle(p, o, a, b) - check if p is inside angle aob.
 * Complexity: everything -> O(1).
 */

struct Vec{ 
    ll x, y;
    Vec(ll x=0, ll y=0) : x(x), y(y) {}
    Vec operator+(Vec &v){return {x + v.x, y + v.y};}
    Vec operator-(Vec &v){return {x - v.x, y - v.y};}
    Vec operator*(ll k){return {x * k, y * k};}
    Vec operator/(ll k){return {x / k, y / k};}
};
int sgn(ll x){
    if(x>0) return 1;
    if(x<0) return -1;
    return 0;
}
auto dot(const Vec& a, const Vec& b){
    return a.x * b.x + a.y * b.y;        
}
auto cross(const Vec& a, const Vec& b){
    return a.x * b.y - a.y * b.x;        
}
auto len2(const Vec& a){return dot(a, a);}
istream& operator>>(istream& in, Vec& a){
    return in >> a.x >> a.y;
} 
ostream& operator<<(ostream& out, Vec& a){
    return out << a.x << " " << a.y;
}
long double angle(Vec &a, Vec &b){
    return atan2(cross(a,b), dot(a,b));
}


//Comparator for sorting vectors by polar angle
bool top(Vec a){ //top halfplane check
    return a.y>0 || (a.y==0 && a.x>0);
}
bool cmp(Vec a, Vec b){
    if(top(a)!=top(b))
        return top(a);
    return cross(a,b)>0;
}

//Check if p inside angle aob
bool in_angle(Vec p, Vec o, Vec a, Vec b){
    return sgn(cross(a-o,p-o)) * sgn(cross(a-o,b-o)) >= 0
        && sgn(cross(b-o,p-o)) * sgn(cross(b-o,a-o)) >= 0; 
}

