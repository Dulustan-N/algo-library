int n; cin >> n;
vector<int> a(n+1);
for(int i=1; i<=n; ++i) cin >> a[i];
vector<int> ans(n+1,-1);
for(int i=1; i<=n; ++i){
    int x; cin >> x; 
    a[i] -= x;
    if(a[i]>=0){ans[i] = 0;}
}

int Q; cin >> Q;
if(!Q){
    for(int i=1; i<=n; ++i) 
        cin >> a[i]; 
    return;
}

struct Query{
    int l,r,x,y;
};
vector<Query> query(Q);
int B = 500, m = (Q+B-1)/B;
for(int j=0; j<m; ++j){                
    int lb = j*B, rb = min((j+1)*B, Q);
    vector<pair<int,int>> scan(n+1);
    for(int t=lb; t<rb; ++t){
        int l,r,x,y; cin >> l >> r >> x >> y;
        query[t] = {l,r,x,y};
        scan[l].first += x; 
        scan[l].second += y;
        if(r<n){
            scan[r+1].first -= x+(r+1-l)*y;
            scan[r+1].second -= y;
        }
    }
    int bal=0, diff=0;
    vector<int> done;
    vector<int> a0 = a;        
    for(int i=1; i<=n; ++i){                        
        bal += diff + scan[i].first;
        a[i] += bal;
        if(a[i]>=0 && ans[i]==-1)
            done.push_back(i);
        diff += scan[i].second;      
    }
    for(auto i : done){
        for(int t=lb; t<rb; ++t){
            if(query[t].l<=i && i<=query[t].r){
                a0[i] += (query[t].x + (i-query[t].l)*query[t].y);
                if(a0[i]>=0){
                    ans[i] = t+1;
                    break;
                }
            }            
        }
    }
} 
