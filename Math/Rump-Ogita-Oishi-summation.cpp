Rump-Ogita-Oishi summation:
//without optimizations
ld two_sum(ld &t, ld a, ld b) {
    ld s = a + b;
    ld bs = s - a;
    ld as = s - bs;
    t = (b - bs) + (a - as);
    return s;
}
ld e;
for(int i = 0; i < 10; ++i){
    nu = two_sum(e, nu, temp[i]);
    num += e;
}
