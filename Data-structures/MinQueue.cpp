/**
 * Queue with support of min.
 * push(x) - push x to the back.
 * pop() - pop 1 element from the front.
 * get() - get min of elements in queue.
 * size() - size of queue.
 * Complexity: push, get, size -> O(1), pop -> amortized O(1).
*/
struct MinQueue{
    stack<pair<int,int>> st0, st1;
    void push(int x){
        auto y = st0.empty() ? x : min(st0.top().S, x);
        st0.push({x,y});
    }
    void pop(){
        if(st1.empty()){
            while(!st0.empty()){
                auto x = st0.top().F;
                st0.pop();
                auto y = st1.empty() ? x : min(st1.top().S, x);
                st1.push({x,y});
            }
        }
        st1.pop();
    }
    int get(){
        if(st0.empty()) return st1.top().S;
        if(st1.empty()) return st0.top().S;
        return min(st0.top().S, st1.top().S);
    }
    int size(){
        return st0.size() + st1.size();
    }
};
