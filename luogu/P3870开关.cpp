#include <iostream>
#include <vector>
using namespace std;
class segtree{
    vector<int> vec;
    vector<int> tag;
    int t;
    void pushup(int p){
        vec[p] = vec[p * 2] + vec[p * 2 + 1];
    }
    void pushdown(int s, int t, int p){
        if(tag[p] && s != t){
            int mid = (s + t) >> 1;
            if(tag[p] % 2){
                vec[p * 2] = (mid - s + 1) - vec[p * 2]; 
                vec[p * 2 + 1] = (t - mid) - vec[p * 2 + 1]; 
            }
            tag[p * 2] += tag[p]; tag[p * 2 + 1] += tag[p];
            tag[p] = 0;
            pushup(p); 
        }
    }
    void update(int l, int r, int s, int t, int p){
        if(l <= s && t <= r){
            vec[p] = (t - s + 1) - vec[p];
            tag[p]++;
            return ;
        }
        int mid = (s + t) >> 1;
        pushdown(s, t, p);
        if(l <= mid) update(l, r, s, mid, p * 2);
        if(mid < r) update(l, r, mid + 1, t, p * 2 + 1);
        pushup(p);
    }
    int getsum(int l, int r, int s, int t, int p){
        if(l <= s && t <= r){
            return vec[p];
        }
        int mid = (s + t) >> 1;
        pushdown(s, t, p);
        int sum = 0;
        if(l <= mid) sum += getsum(l, r, s, mid, p * 2);
        if(mid < r) sum += getsum(l, r, mid + 1, t, p * 2 + 1);
        return sum;
    }
public:
    segtree(int size){
        vec.assign(4 * size + 5, 0);
        tag.assign(4 * size + 5, 0);
        t = size;
    }
    void update(int l, int r){
        update(l - 1, r - 1, 0, t, 1);
    }
    int getsum(int l, int r){
        return getsum(l - 1, r - 1, 0, t, 1);
    }
};
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    segtree sgt(n);
    while(m--){
        int opt, a, b;
        cin >> opt >> a >> b;
        if(opt == 0){
            sgt.update(a, b);
        }else{
            cout << sgt.getsum(a, b) << '\n';
        }
    }
    return 0;
}