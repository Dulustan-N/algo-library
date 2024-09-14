/**
 * Quadratic sorting algorthims:
 * Selection Sort, Bubble Sort, Insertion sort.
 * Complexity: time -> O(n^2).
*/

//Selection Sort
void selection_sort(vector<int> &a){
    int n = a.size();
    for(int i=0; i<n-1; i++) {
        int imin = i;
        for(int j=i+1; j<n; j++){
            if(a[j]<a[imin])
                imin = j;
        }
        swap(a[i], a[imin]);
   }   
}


//Bubble Sort
void bubble_sort(vector<int> &a){
    int n = a.size();
    for(int i=n-1; i>=1; i--){
        bool is_sorted = true;
        for(int j=0; j<=i; j++)
            if(a[j]>a[j+1]){
                swap(a[j],a[j+1]);
                is_sorted = false;
            }  
        if(is_sorted)
            break;          
    }    
}


//Insertion Sort
void insertion_sort(vector<int> &a){
    int n = a.size();
    for(int i=1; i<n; i++){
        int nxt = a[i];
        int j = i-1;
        while(j>=0 && a[j]>nxt){
            a[j+1] = a[j];
            --j;
        }
        a[j+1] = nxt;
    }  
}