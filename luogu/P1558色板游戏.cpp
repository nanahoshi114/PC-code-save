#include <iostream>
#include <vector>
using namespace std;
class segtree_bit{
    vector<int> tree;
    vector<int> tag;
    int size;
    void pushup(int p){
        tree[p] = tree[p * 2] | tree[p * 2 + 1];
    }
    void pushdown(int s, int t, int p){
        if(tag[p] && s != t){
            tree[p * 2] = tree[p * 2 + 1] = tag[p];
            tag[p * 2] = tag[p * 2 + 1] = tag[p];
            tag[p] = 0;
            pushup(p);
        }
    }
    void update(int l, int r, int s, int t, int p, int x){
        if(l <= s && t <= r){
            tree[p] = x;
            tag[p] = x;
            return ;
        }
        pushdown(s, t, p);
        int mid = s + ((t - s) >> 1);
        if(l <= mid) update(l, r, s, mid, p * 2, x);
        if(mid < r) update(l, r, mid + 1, t, p * 2 + 1, x);
        pushup(p);
    }
    int rangesum(int l, int r, int s, int t, int p){
        if(l <= s && t <= r){
            return tree[p];
        }
        pushdown(s, t, p);
        int sum = 0;
        int mid = s + ((t - s) >> 1);
        if(l <= mid) sum |= rangesum(l, r, s, mid, p * 2);
        if(mid < r) sum |= rangesum(l, r, mid + 1, t, p * 2 + 1);
        return sum;
    }
public:
    segtree_bit(int _size) : size(_size){
        tree.resize(4 * size + 5, 1);
        tag.resize(4 * size + 5, 0);
    }
    void update(int l, int r, int x){
        update(l, r, 1, size, 1, x);
    }
    int rangesum(int l, int r){
        return rangesum(l, r, 1, size, 1);
    }
};
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int L, T, O;
    cin >> L >> T >> O;
    segtree_bit stb(L);
    auto count = [](int x){
        int cnt = 0;
        while(x){
            cnt += (x & 1);
            x >>= 1;
        }
        return cnt;
    };
    while(O--){
        char opt;
        cin >> opt;
        if(opt == 'C'){
            int l, r, c;
            cin >> l >> r >> c;
            if(l > r) swap(l, r);
            stb.update(l, r, 1 << (c - 1));
        }else{
            int l, r;
            cin >> l >> r;
            if(l > r) swap(l, r);
            cout << count(stb.rangesum(l, r)) << '\n';
        }
    }
    return 0;
}