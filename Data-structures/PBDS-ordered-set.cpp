/**
 * Template to use PBDS ordered_set structures:
 * ordered_set<T>, ordered_map<T,V> - all methods of set<T>, map<T,V> except count().
 * s.find_by_order(k) - find k-th (0-based index) element of s by order.
 * s.order_of_key(x) - find the order of element with key x.
 * 
 * ordered_multiset<T>:
 *      lower_bound(x) <-> upper_bound(x)
 *      s.find(x) always returns s.end(), instead use: 
 *      s.upper_bound(x), or
 *      s.find_by_order(s.order_of_key(x)).
*/

#include<ext/pb_ds/assoc_container.hpp> 
#include<ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 

template<class T>
using ordered_set = tree<T, null_type, less<T>, 
        rb_tree_tag,tree_order_statistics_node_update>;

template<class T, class V>
using ordered_map = tree<T, V, less<T>, 
        rb_tree_tag, tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, 
        rb_tree_tag,tree_order_statistics_node_update>;
