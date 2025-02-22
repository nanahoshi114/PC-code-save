#include <iostream>
#include <vector>
using namespace std;
class BIT{
    vector<int> tree;
    int lowbit(int x){
        return x & -x;
    }
    int size;
    int query(int x){
        int sum = 0;
        while(x){
            sum ^= tree[x];
            x -= lowbit(x);
        }
        return sum;
    }
public:
    BIT(const vector<int> &org, int _size) : size(_size){
        tree.resize(size + 1, 0);
        for(int i = 1; i <= size; i++){
            for(int j = i; j <= size; j += lowbit(j)){
                tree[j] ^= org[i];
            }
        }
    }
    void update(int x, int ind){
        for(int i = ind; i <= size; i += lowbit(i)){
            tree[i] ^= x;
        }
    }
    int query(int l, int r){
        return query(r) ^ query(l - 1);
    }
};
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> org(n + 1, 0);
    vector<int> odd(1, 0), even(1, 0);
    for(int i = 1, t; i <= n; i++){
        cin >> t;
        org[i] = t;
        if(i % 2) odd.push_back(t);
        else even.push_back(t);
    }
    BIT obit(odd, odd.size() - 1), ebit(even, even.size() - 1);
    while(q--){
        int opt, l, r;
        cin >> opt >> l >> r;
        if(opt == 1){
            if(l % 2){
                obit.update(org[l], l / 2 + 1);
                org[l] = r;
                obit.update(r, l / 2 + 1);
            }else{
                ebit.update(org[l], l / 2);
                org[l] = r;
                ebit.update(r, l / 2);
            }
        }else{
            if((r - l + 1) % 2 == 0){
                cout << 0;
            }else{
                if(l % 2){
                    cout << obit.query(l / 2 + 1, r / 2 + 1);
                }else{
                    cout << ebit.query(l / 2, r / 2);
                }
            }
            cout << '\n';
        }
    }
    return 0;
}