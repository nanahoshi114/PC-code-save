#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int gcd(int x, int y){
    if(y == 0) return x;
    return gcd(y, x % y);
}
class sparseTable{
    //vector<int> *_org;
    vector<vector<int>> ST;
    vector<int> lgn;
public:
    sparseTable(const vector<int> &org){
        //_org = &org;
        int sz = org.size() - 2;
        lgn.assign(sz + 5, 0);
        lgn[1] = 0, lgn[2] = 1;
        for(int i = 3; i <= sz; i++){
            lgn[i] = lgn[i / 2] + 1;
        }
        ST.assign(sz + 5, vector<int>(lgn[sz] + 5));
        for(int i = 1; i <= sz; i++){
            ST[i][0] = abs(org[i] - org[i + 1]);
        }
        for(int j = 1; j <= lgn[sz]; j++){
            int pj = (1 << (j - 1));
            for(int i = 1; i + pj <= sz; i++){
                ST[i][j] = gcd(ST[i][j - 1], ST[i + pj][j - 1]);
            }
        }
    }
    int query(int l, int r){
        if(l == r) return 0;
        r--;
        int pj = lgn[r - l + 1];
        return gcd(ST[l][pj], ST[r - (1 << pj) + 1][pj]);
    }
};
void slv(){
    int n, q, l, r;
    cin >> n >> q;
    vector<int> vec(n + 1, 0);
    for(int i = 1; i <= n; i++){
        cin >> vec[i];
    }
    sparseTable st(vec);
    while(q--){
        cin >> l >> r;
        cout << st.query(l, r) << ' ';
    }
    cout << '\n';
}
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) slv();    
    return 0;
}