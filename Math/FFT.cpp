/**
 * O(n log n) Fast Fourier Transformation
 * c = conv(a, b) - convolution of a and b:
 * c[i] = a[0]*b[i] + a[1]*b[i-1] + ... + a[i]*b[0].
 * a.size = n, b.size = m.
 * Complexity: time -> O(n+m), space -> O((n+m) log(n+m)).
*/

const double PI = acos(-1);
struct base{
    double a, b;
    base(double a = 0, double b = 0) : a(a), b(b) {}
    const base operator + (const base &c) const
    {return base(a + c.a, b + c.b);}
    const base operator - (const base &c) const
    {return base(a - c.a, b - c.b);}
    const base operator * (const base &c) const
    {return base(a * c.a - b * c.b, a * c.b + b * c.a);}
};

void fft(vector<base> &a, bool inv = 0){
    int n = a.size(), i = 0;
    for(int j = 1; j < n - 1; ++j) {
        for(int k = n >> 1; k > (i ^= k); k >>= 1);
        if(j<i) swap(a[i], a[j]);
    }
    for(int l=1, m; (m=l<<1)<=n; l<<=1){
        double ang = 2 * PI / m;
        base wn = base(cos(ang), (inv ? 1. : -1.) * sin(ang)), w;
        for(int i=0,j,k; i<n; i+=m){
            for(w=base(1, 0), j=i, k=i+l; j<k; ++j, w=w*wn){
                base t = w * a[j+l];
                a[j+l] = a[j]-t;
                a[j] = a[j]+t;
            }
        }
    }
    if(inv) for(int i=0; i<n; ++i) a[i].a /= n, a[i].b /= n;
}

template<typename T>
vector<T> conv(vector<T> &a, vector<T> &b){
    int n = a.size(), m = b.size(), sz = 1;
    while(sz < n+m-1) sz <<= 1;
    vector<base> x(sz), y(sz), z(sz);
    for(int i=0; i<sz; ++i){
        x[i] = i < (int)a.size() ? base(a[i], 0) : base(0, 0);
        y[i] = i < (int)b.size() ? base(b[i], 0) : base(0, 0);
    }
    fft(x), fft(y);
    for(int i=0; i<sz; ++i) z[i] = x[i] * y[i];
    fft(z, 1);
    vector<T> ret(sz);
    for(int i=0; i<sz; ++i) ret[i] = (ll)round(z[i].a);
    while((int)ret.size() > n+m-1) ret.pop_back();
    return ret;
}
