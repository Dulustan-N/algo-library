double rnd(){return double(rand()) / RAND_MAX;}

double temp = 1;
auto ans = calc();
while(clock() / (double)CLOCKS_PER_SEC <= 1.9){
    //do small change
    auto cur = calc();
    ans = min(ans, cur);
    if(cur < ans || rnd() < exp(-(cur - ans) / temp){
        ans = cur;
    }
    else{
        //rollback the change
    }
    temp *= 0.9999;
}
