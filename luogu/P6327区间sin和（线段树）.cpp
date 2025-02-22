#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
using ll = long long;
class segtree{
    const int M = 1e6 + 5;
    struct Node{
        double sin, cos;
    };
    vector<Node> tree;
    vector<ll> tag;
    vector<double> presin, precos;
    int size;
    void precal(ll x){
        if(presin[x] == 0){
            presin[x] = sin(x); precos[x] = cos(x);
        }
    }
    void plus(ll pln, Node &x){
        double psin = x.sin;
        if(pln >= M){
            double plnsin = sin(pln), plncos = cos(pln);
            x.sin = plnsin * x.cos + plncos * x.sin;
            x.cos = plncos * x.cos - plnsin * psin;
        }else{
            precal(pln);
            x.sin = presin[pln] * x.cos + precos[pln] * x.sin;
            x.cos = precos[pln] * x.cos - presin[pln] * psin;
        }
    }
    void pushup(int p){
        tree[p].sin = tree[p * 2].sin + tree[p * 2 + 1].sin;
        tree[p].cos = tree[p * 2].cos + tree[p * 2 + 1].cos; 
    }
    void pushdown(int s, int t, int p){
        if(tag[p] && s != t){
            tag[p * 2] += tag[p];
            tag[p * 2 + 1] += tag[p];
            plus(tag[p], tree[p * 2]);
            plus(tag[p], tree[p * 2 + 1]);
            tag[p] = 0;
            pushup(p);
        }
    }
    void build(const vector<int> &org, int s, int t, int p){
        if(s == t){
            precal(org[s]);
            tree[p].sin = presin[org[s]];
            tree[p].cos = precos[org[s]];
            return ;
        }
        int mid = (s + t) >> 1;
        build(org, s, mid, p * 2);
        build(org, mid + 1, t, p * 2 + 1);
        pushup(p);
    }
    void update(int l, int r, int s, int t, int p, ll val){
        if(l <= s && t <= r){
            plus(val, tree[p]);
            tag[p] += val;
            return ;
        }
        pushdown(s, t, p);
        int mid = (s + t) >> 1;
        if(l <= mid) update(l, r, s, mid, p * 2, val);
        if(mid < r) update(l, r, mid + 1, t, p * 2 + 1, val);
        pushup(p);
    }
    double query_sin(int l, int r, int s, int t, int p){
        if(l <= s && t <= r){
            return tree[p].sin;
        }
        pushdown(s, t, p);
        int mid = (s + t) >> 1;
        double res = 0;
        if(l <= mid) res += query_sin(l, r, s, mid, p * 2);
        if(mid < r) res += query_sin(l, r, mid + 1, t, p * 2 + 1);
        return res;
    }
public:
    segtree(const vector<int> &org, int _size) : size(_size){
        tree.resize(4 * size + 5, {});
        tag.resize(4 * size + 5, 0);
        presin.resize(M, 0);
        precos.resize(M, 0);
        build(org, 1, size, 1);
    }
    void update(int l, int r, ll val){
        update(l, r, 1, size, 1, val);
    }
    double query_sin(int l, int r){
        return query_sin(l, r, 1, size, 1);
    }
};
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(nullptr);
    int n, m;
    cin >> n;
    vector<int> org(n + 1, 0);
    for(int i = 1; i <= n; i++){
        cin >> org[i];
    }
    segtree sgt(org, n);
    cin >> m;
    while(m--){
        int opt, l, r, v;
        cin >> opt >> l >> r;
        if(opt == 1){
            cin >> v;
            sgt.update(l, r, v);
        }else{
            cout << fixed << setprecision(1) << sgt.query_sin(l, r) << '\n';
        }
    }
    return 0;
}