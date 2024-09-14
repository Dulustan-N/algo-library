/**
 * Quick Sort.
 * Complexity: time -> O(n log n).
*/

void quick_sort(vector<int> &a, int l, int r){
    if(r <= l) return;
    int i = l, j = r;
    int pivot = a[(l+r)/2];
    while(i <= j){
        while(a[i] < pivot) ++i;
        while(a[j] > pivot) --j;
        if(i <= j){
            swap(a[i],a[j]);
            ++i; --j;   
        }
    }
    quick_sort(a, l, j);
    quick_sort(a, i, r);
}  