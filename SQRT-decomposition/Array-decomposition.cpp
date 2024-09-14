/**
 * SQRT-decomposition example.
 * Problem: array a[0]..a[n-1], two types of queries:
 *          Query 1: number of elements less than x on [l,r],
 *          Query 2: add +x on [l,r].
 */

int n,q; cin >> n >> q;
const int B = 500;
int m = (n+B-1)/B;
vl a(n); forn(i,0,n) cin >> a[i];

vector<ll> b = a;   
vector<ll> c(m);

for(int j=0; j<m; ++j)        
    sort(b.begin() + j*B, b.begin() + min((j+1)*B,n));    

while(q--){
    int req,l,r,x; cin >> req >> l >> r >> x; --l;
    int lb = l/B, rb = (r-1)/B;
    if(req==1){
        int cnt=0;
        if(lb == rb){
            for(int i=l; i<r; ++i)
                if(a[i]+c[lb] < x)
                    ++cnt;
        }
        else{
            for(int i=l; i<(lb+1)*B; ++i)
                if(a[i]+c[lb] < x)
                    ++cnt;
            for(int j=lb+1; j<rb; ++j){
                cnt += lower_bound(b.begin()+j*B, b.begin()+(j+1)*B, x-c[j]) 
                    - b.begin() - j*B;
            }
            for(int i=rb*B; i<r; ++i)
                if(a[i]+c[rb] < x)
                    ++cnt;
        }
        cout << cnt << "\n";
    }
    else{
        if(lb == rb){
            for(int i=l; i<r; ++i)
                a[i] += x;
            copy(a.begin()+lb*B, a.begin()+min((lb+1)*B,n), b.begin()+lb*B);
            sort(b.begin()+lb*B, b.begin()+min((lb+1)*B,n));
        }
        else{
            for(int i=l; i<(lb+1)*B; ++i)
                a[i] += x;
            for(int j=lb+1; j<rb; ++j)
                c[j] += x;
            for(int i=rb*B; i<r; ++i)
                a[i] += x;
            copy(a.begin()+lb*B, a.begin()+(lb+1)*B, b.begin()+lb*B);
            sort(b.begin()+lb*B, b.begin()+(lb+1)*B);
            copy(a.begin()+rb*B, a.begin()+min((rb+1)*B,n), b.begin()+rb*B);
            sort(b.begin()+rb*B, b.begin()+min((rb+1)*B,n));
        }
    }
}
