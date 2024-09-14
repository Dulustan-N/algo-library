/**
 * Problem: n points on plane, find the closest pair of points.
 * Solution 1 - scanline method -> O(n log n)
 * Solution 2 - euristic method -> ?
 */

// Scanline method
ll closest_pair(vector<Vec> p){
    int n=p.size();
    sort(p.begin(), p.end(), [](Vec v, Vec u){
        return v.x < u.x;
    });

    set<pair<ll,ll>> s;
    ll best=INF_LL;
    for(int l=0, r=0; r<n; ++r){
        ll d=ceil(sqrt(best));
        while(p[r].x-p[l].x > d){
            s.erase({p[l].y, p[l].x});
            ++l;
        }
        auto it1 = s.lower_bound({p[r].y-d, p[r].x});
        auto it2 = s.upper_bound({p[r].y+d, p[r].x});
        for(auto it=it1; it!=it2; ++it){
            Vec a(it->second, it->first);
            best = min(best, len2(a-p[r]));
        }
        s.insert({p[r].y, p[r].x});        
    }
    return best;      
}

// Euristic method
ll closest_pair(vector<Vec> p){
    int n=p.size();
    mt19937 gen(time(0));
    Vec q(gen()%1000, gen()%1000);
    ld lenq(sqrtl(len2(q)));
    
    sort(p.begin(), p.end(), [&](Vec v, Vec u){
        return dot(v,q) < dot(u,q);
    });
    ll best = len2(p[1]-p[0]);
    for(int l=0,r=1; r<n; ++r){
        ld d=sqrtl(best);
        while(dot(p[r],q)-dot(p[l],q) >= d*lenq)
            ++l;
        for(int i=l; i<r; ++i)
            best = min(best, len2(p[r]-p[i]));
    }    
    return best;      
}


