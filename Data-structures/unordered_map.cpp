/**
 * How to include chash:
 * unordered_map<int, int, chash> mp;  
 * unordered_set<int, chash> s;  
 * gp_hash_table<int, int, chash> mp; //map
 * gp_hash_table<int, null_type, chash> s; //set 
 */

// Fast and pretty good custom hash
struct chash{
    size_t operator()(int x) const{
        static const int RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        x ^= RANDOM;
        return x ^ (x >> 16);
    }
};

// Unhackable custom hash
struct chash{
    static int splitmix64(int x){
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(int x) const{
        static const int RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + RANDOM);
    }
};

//include gp hash table
#include<ext/pb_ds/assoc_container.hpp> 
using namespace __gnu_pbds; 
