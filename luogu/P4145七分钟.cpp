#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using ll = long long;
class BIT{
    vector<ll> tree;
    int size;
    int lowbit(int x){
        return x & -x;
    }
    ll query(ll x){
        ll sum = 0;
        while(x){
            sum += tree[x];
            x -= lowbit(x);
        }
        return sum;
    }
public:
    BIT(const vector<ll> &org, int _size) : size(_size){
        tree.resize(size + 5, 0);
        for(int i = 1; i <= size; i++){
            for(int j = i; j <= size; j += lowbit(j)){
                tree[j] += org[i];
            }
        }
    }
    void update(int ind, ll val){
        for(int i = ind; i <= size; i += lowbit(i)){
            tree[i] += val;
        }
    }
    ll query(int l, int r){
        return query(r) - query(l - 1);
    }
};
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n, m;
    cin >> n;
    vector<ll> org(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> org[i];
    }
    BIT bt(org, n);
    cin >> m;
    while(m--){
        int k, l, r;
        cin >> k >> l >> r;
        if(l > r) swap(l, r);
        if(k == 0){
            if(bt.query(l, r) > (r - l + 1)){
                for(int i = l; i <= r; i++){
                    bt.update(i, -org[i]);
                    org[i] = sqrt(org[i]);
                    bt.update(i, org[i]);
                }
            }
        }else{
            cout << bt.query(l, r) << '\n';
        }
    }
    return 0;
}