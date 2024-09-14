/**
 * Persistent Stack.
 * Node: val - value in the node, nx - number of the next node.
 * t[0] - empty node with nx = -1.
 * push(p, x) - push number x to the node p, return number of new node.
 * pop(p) - "pop" from node p, return number of next node.
 * need to use separate array ver[]:
 * ver[i] - number of top node of version i.
 */

struct PerStack{
    struct Node{
        int val, nx;
        Node(int val, int nx) : val(val), nx(nx){}
    };
    vector<Node> t;    
    PerStack(){t.push_back(Node(0, -1));}
    int push(int p, int x){
        t.push_back(Node(x, p));
        return t.size()-1;
    }
    int pop(int p){return t[p].nx;}
};  

vector<int> ver;