/**
 * O(n log n) Fast Fourier Transformation
 * c = conv(a, b) - convolution of a and b:
 * c[i] = a[0]*b[i] + a[1]*b[i-1] + ... + a[i]*b[0].
 * a.size = n, b.size = m, c.size = n + m - 1
 * Complexity: time -> O(n+m), space -> O((n+m) log(n+m)).
*/

using cd = complex<double>;
const double PI = acos(-1);
 
void fft(vector<cd> & a, bool inv = 0){
    int n = a.size();
    for(int i=1, j=0; i<n; ++i){
        int bit = n >> 1;
        for(; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }
    for(int len=2; len<=n; len<<=1){
        double ang = 2 * PI / len * (inv ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for(int i=0; i<n; i+=len){
            cd w(1);
            for(int j=0; j<len/2; ++j){
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if(inv){
        for(cd &x : a) x /= n;
    }
}
 
template<typename T>
vector<T> conv(vector<T> &a, vector<T> &b){
    int n = a.size(), m = b.size(), s = 1;
    while(s < n+m-1) s <<= 1;
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(s); fb.resize(s);
    fft(fa), fft(fb);
    for(int i=0; i<s; ++i) fa[i] *= fb[i];
    fft(fa, 1);
    vector<T> c(n+m-1);
    for(int i=0; i<n+m-1; ++i) c[i] = round(fa[i].real());
    return c;
}