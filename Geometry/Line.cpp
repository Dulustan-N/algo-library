/**
 * struct for lines on plane.
 * Line(a, b, c): a * x^2 + b * x + c = 0.
 * Line(p, q): line through points p and q.
 * intersect(a, b, c, d) - check if segments ab and cd intersect.
 * intersect(l1, l2) - find intersection of lines l1 and l2.
 * dist_to_seg(p, a, b) - find distance from p to segment ab. 
 * Complexity: everything -> O(1).
 */

struct Line{
    ll a, b, c;
    Line(ll a=0, ll b=0, ll c=0) : a(a), b(b), c(c) {}
    Line(Vec p, Vec q) : a(p.y-q.y), b(q.x-p.x), c(-a * p.x - b * p.y) {}  
    ld norm(){return sqrtl(a*a + b*b);}
};

//check if segments ab and cd intersect
bool intersect(Vec a, Vec b, Vec c, Vec d){
    if(cross(b-a, d-c)!=0)
        return sgn(cross(b-a,c-a)) * sgn(cross(b-a,d-a)) <= 0
        && sgn(cross(d-c,a-c)) * sgn(cross(d-c,b-c)) <= 0;
    if(cross(b-a,c-a)!=0) return false;
    return dot(c-a,c-b)<=0 || dot(d-a,d-b)<=0
    || dot(a-c,b-d)<=0 || dot(b-c,b-d)<=0;
}

//Intersection of lines
Vec intersect(Line l1, Line l2){
    return {(ld)(l2.c * l1.b - l1.c * l2.b) / (l1.a * l2.b - l2.a * l1.b),
        (ld)(l2.c * l1.a - l1.c * l2.a) / (l2.a * l1.b - l1.a * l2.b)};
}

//Distance from p to segment ab
ld dist_to_seg(Vec p, Vec a, Vec b){
    if(dot(b-a,p-a)<0) return sqrtl(len2(p-a));
    if(dot(a-b,p-b)<0) return sqrtl(len2(p-b));
    return abs(cross(p-a,b-a)) / sqrtl(len2(b-a));
}