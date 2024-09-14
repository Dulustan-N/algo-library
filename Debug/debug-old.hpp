#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define deb(x) cerr << #x <<" = "; _print(x); cerr << "\n";

void _print(int t){cerr << t;}
void _print(ll t){cerr << t;}
void _print(string t){cerr << t;}
void _print(char t){cerr << t;}
void _print(double t){cerr << t;}
template<class T> void _print(vector <T> v);
template<class T> void _print(set <T> v);
template<class T> void _print(multiset <T> v);
template<class T> void _print(unordered_set <T> v);
template<class T> void _print(unordered_multiset <T> v);
template<class T> void _print(deque <T> v);
template<class T, class V> void _print(pair <T, V> p);
template<class T, class V> void _print(map <T, V> v);
template<class T, class V> void _print(unordered_map <T, V> v);
template<class T> void _print(vector <T> v){cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template<class T> void _print(set <T> v){cerr << "{ "; for (T i : v) {_print(i); cerr << " ";} cerr << "}";}
template<class T> void _print(multiset <T> v){cerr << "{ "; for (T i : v) {_print(i); cerr << " ";} cerr << "}";}
template<class T> void _print(unordered_set <T> v){cerr << "{ "; for (T i : v) {_print(i); cerr << " ";} cerr << "}";}
template<class T> void _print(unordered_multiset <T> v){cerr << "{ "; for (T i : v) {_print(i); cerr << " ";} cerr << "}";}
template<class T> void _print(deque <T> v){cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template<class T, class V> void _print(pair <T, V> p){cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
template<class T, class V> void _print(map <T, V> v){cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template<class T, class V> void _print(unordered_map <T, V> v){cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";};
