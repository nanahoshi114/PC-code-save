#include <iostream>
#include <vector>
#include <numeric>
using namespace std;
class dsu{
    vector<int> pa;
public:
    dsu(int size){
        pa.resize(size + 5);
        iota(pa.begin(), pa.end(), 0);
    }
    int find(int x){
        return pa[x] == x ? x : pa[x] = find(pa[x]);
    }
    void unite(int x, int y){
        pa[find(y)] = find(x); 
    }
};
int main(){
    int n, k, ans = 0;
    cin >> n >> k;
    dsu ds(3 * n);
    while(k--){
        int opt, x, y;
        cin >> opt >> x >> y;
        if(x > n || y > n){
            ans++;
            continue;
        }
        if(opt == 1){
            if(ds.find(x + n) == ds.find(y) || ds.find(x + 2 * n) == ds.find(y)){
                ans++;
                continue;
            }
            ds.unite(x, y);
            ds.unite(x + n, y + n);
            ds.unite(x + 2 * n, y + 2 * n);
        }else{
            if(ds.find(x) == ds.find(y) || ds.find(x + 2 * n) == ds.find(y)){
                ans++;
                continue;
            }
            ds.unite(x + n, y);
            ds.unite(y + 2 * n, x);
            ds.unite(x + 2 * n, y + n);
        }
    }
    cout << ans;
    return 0;
}