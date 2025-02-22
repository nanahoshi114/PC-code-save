#include <iostream>
#include <algorithm>
#include <array>
using namespace std;
using ll = long long;
const int M = 5e5 + 5;
struct Node{
    int val, ind;
    bool operator>(Node r) const {
        if(val != r.val){
            return val > r.val;
        }
        return ind > r.ind;
    }
};
array<Node, M> arr;
class BIT{
    int lowbit(int x){
        return x & -x;
    }
    array<ll, M> tree;
    int size;
public:
    BIT(){
        tree.fill(0);
    }
    void init(int _size){
        size = _size;
    }
    void add(int ind, ll val){
        for(int i = ind; i <= size; i += lowbit(i)){
            tree[i] += val;
        }
    }
    ll query(int x){
        ll ans = 0;
        while(x){
            ans += tree[x];
            x -= lowbit(x);
        }
        return ans;
    }
}bt;
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> arr[i].val;
        arr[i].ind = i;
    }
    sort(arr.begin() + 1, arr.begin() + 1 + n, greater<Node>()); //ÀëÉ¢²Ù×÷
    ll ans = 0;
    bt.init(n);
    for(int i = 1, qind; i <= n; i++){
        ans += bt.query(arr[i].ind - 1);
        bt.add(arr[i].ind, 1);
    }
    cout << ans;
    return 0;
}