#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
using ll = long long;
struct Opt{
    bool fl;
    int l, r;
};
struct SegTree{
    vector<int> tree;
    vector<int> tag;
    int range;
    void pushup(int p){
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
    void build(const vector<int> &org, int p, int l, int r){
        if(l == r){
            tree[p] = org[l];
            return ;
        }
        int mid = (l + r) >> 1;
        build(org, p * 2, l, mid);
        build(org, p * 2 + 1, mid + 1, r);
        pushup(p);
    }
    SegTree(const vector<int> &__org) : range(__org.size() - 1){
        tree.resize(__org.size() << 2);
        tag.resize(__org.size() << 2, -1);
        build(__org, 1, 1, range);
    }
    void pushdown(int p, int l, int r){
        if(tag[p] != -1 && l != r){
            int mid = (l + r) >> 1;
            tree[p * 2] = (mid - l + 1) * tag[p];
            tree[p * 2 + 1] = (r - mid) * tag[p];
            tag[p * 2 + 1] = tag[p * 2] = tag[p];
            tag[p] = -1;
        }
    }
    void update(int p, int l, int r, int fl, int fr, int val){
        if(fl <= l && r <= fr){
            tree[p] = val * (r - l + 1);
            tag[p] = val;
            return ;
        }
        int mid = (l + r) >> 1;
        pushdown(p, l, r);
        if(fl <= mid) update(p * 2, l, mid, fl, fr, val);
        if(mid < fr) update(p * 2 + 1, mid + 1, r, fl, fr, val);
        pushup(p);
    }
    int query(int p, int l, int r, int fl, int fr){
        if(fl <= l && r <= fr){
            return tree[p];
        }
        int mid = (l + r) >> 1;
        pushdown(p, l, r);
        int res = 0;
        if(fl <= mid) res += query(p * 2, l, mid, fl, fr);
        if(mid < fr) res += query(p * 2 + 1, mid + 1, r, fl, fr);
        return res;
    }
    int query(int l, int r){
        return query(1, 1, range, l, r);
    }
    void update(int l, int r, int val){
        if(l > r) return ;
        update(1, 1, range, l, r, val);
    }
};
int main(){
    //freopen("testin.txt", "r", stdin);
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    vector<Opt> opt(m + 1);
    for(int i = 1; i <= m; i++){
        cin >> opt[i].fl >> opt[i].l >> opt[i].r;
    }
    vector<int> org(n + 1);
    int query;
    cin >> query;
    auto check = [&](int x){
        for(int i = 1; i <= n; i++){
            org[i] = (a[i] > x);
        }
        SegTree sgt(org);
        for(int i = 1; i <= m; i++){
            int cnt1 = sgt.query(opt[i].l, opt[i].r);
            if(opt[i].fl){
                sgt.update(opt[i].l, opt[i].l + cnt1 - 1, 1);
                sgt.update(opt[i].l + cnt1, opt[i].r, 0);
            }else{
                sgt.update(opt[i].r - cnt1 + 1, opt[i].r, 1);
                sgt.update(opt[i].l, opt[i].r - cnt1, 0);
            }
        }
        return sgt.query(query, query);
    };
    int l = 1, r = n, mid;
    while(l < r){
        mid = (l + r) >> 1;
        if(check(mid)){
            l = mid + 1;
        }else{
            r = mid;
        }
    }
    cout << l << '\n';
    //println("{}", l);
    return 0;
}