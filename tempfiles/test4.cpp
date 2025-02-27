#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;
using ll = long long;
struct segtree{
    struct Node{
        int sum, ls, rs;  
    };
    vector<Node> tree;
    segtree(int range){
        tree.push_back({});
    }
    void update(int &p, int l, int r, int now){
        if(!p){
            p = tree.size();
            tree.push_back({});
        }
        tree[p].sum++;
        int mid = (l + r) >> 1;
        if(now <= mid) update(tree[p].ls, l, mid, now);
        else update(tree[p].rs, mid + 1, r, now);
    }
    int query(int &p, int l, int r, int fl, int fr){
        if(!p) return 0;
        if(fl <= l && r <= fr) return tree[p].sum;
    }
};
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    
    return 0;
}