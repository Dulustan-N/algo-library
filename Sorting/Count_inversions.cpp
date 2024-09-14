/**
 * Count a number of inversions in vector v by using Merge Sort.
 * Complexity: time -> O(n log n).
*/

ll merge(vector<int>& v, vector<int>& v1, vector<int>& v2){
    int inv = 0;
    int n1 = v1.size(), n2 = v2.size();
    int i1 = 0, i2 = 0;
    while(i1 < n1 && i2 < n2){
        if(v1[i1] <= v2[i2])
            v.push_back(v1[i1++]);
        else{
            v.push_back(v2[i2++]);        
            inv += n1 - i1;
        }
    }
    while(i1 < n1)
        v.push_back(v1[i1++]);
    while(i2 < n2)
        v.push_back(v2[i2++]);    
    return inv;
}

ll inversions(vector<int>& v){
    ll inv = 0;
    int n = v.size();
    if(n <= 1) return 0;
    vector<int> v1(v.begin(), v.begin()+n/2);
    vector<int> v2(v.begin()+n/2, v.end());
    inv += inversions(v1);
    inv += inversions(v2);    
    v.clear();
    inv += merge(v, v1, v2);
    return inv;
}