/**
 * Make tangent lines from point q to convex polygon p.
 * Complexity: time -> O(log n).
 */

auto cmp = [&](int a, int b)->bool{
    return cross(p[a]-q,p[b]-q)>0 || (cross(p[a]-q,p[b]-q)==0 && len2(p[a]-q)<len2(p[b]-q));
};
int l = 0, r = 0;
for(int h=__lg(n); h>=0; --h){
    vector<int> v{l, (l+(1<<h))%n, (l-(1<<h)+n)%n};
    sort(v.begin(), v.end(), cmp);
    l = v[0];
    vector<int> u{r, (r+(1<<h))%n, (r-(1<<h)+n)%n};
    sort(u.begin(), u.end(), cmp);
    r = u[2];
}