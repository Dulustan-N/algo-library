/**
 * Merge Sort.
 * Complexity: time -> O(n log n).
*/

void merge(vector<int>& v, vector<int>& v1, vector<int>& v2){
    int n1 = v1.size(), n2 = v2.size();
    int i1 = 0, i2 = 0;
    while(i1 < n1 && i2 < n2){
        if(v1[i1] <= v2[i2])
            v.push_back(v1[i1++]);
        else
            v.push_back(v2[i2++]);
    }
    while(i1 < n1)
        v.push_back(v1[i1++]);
    while(i2 < n2)
        v.push_back(v2[i2++]);    
}
void merge_sort(vector<int>& v){
    int n = v.size();
    if(n<=1) return;
    vector<int> v1(v.begin(), v.begin()+n/2);
    vector<int> v2(v.begin()+n/2, v.end());
    merge_sort(v1);
    merge_sort(v2);
    v.clear();
    merge(v, v1, v2);
}