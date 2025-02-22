//https://ac.nowcoder.com/acm/contest/95336/L
#include <iostream>
#include <vector>
#include <numeric>
#include <array>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
void slv(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1), b(n + 1);
    array<vector<vector<ll>>, 2> prea, preb;
    prea.fill(vector<vector<ll>>(31, vector<ll>(n + 1)));
    preb.fill(vector<vector<ll>>(31, vector<ll>(n + 1)));
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        for(int j = 0; j < 31; j++){
            prea[a[i] >> j & 1][j][i]++;
        }
    }
    for(int i = 1; i <= n; i++){
        cin >> b[i];
        for(int j = 0; j < 31; j++){
            preb[b[i] >> j & 1][j][i]++;
        }
    }
    for(int j = 0; j < 31; j++){
        for(int k = 0; k < 2; k++){
            partial_sum(prea[k][j].begin() + 1, prea[k][j].end(), prea[k][j].begin() + 1);
            partial_sum(preb[k][j].begin() + 1, preb[k][j].end(), preb[k][j].begin() + 1);
        }
    }
    auto querya = [&](int k, int x, int l, int r){
        return prea[k][x][r] - prea[k][x][l - 1];
    };
    auto queryb = [&](int k, int x, int l, int r){
        return preb[k][x][r] - preb[k][x][l - 1];
    };
    vector<ll> premakel(n + 1);
    for(int i = 1; i <= n; i++){
        for(int j = 0; j < 31; j++){
            premakel[i] = (premakel[i] + ((queryb(!(a[i] >> j & 1), j, i, n)) << j)) % mod;
        }
        premakel[i] = (premakel[i - 1] + premakel[i]) % mod;
    }
    //partial_sum(premakel.begin() + 1, premakel.end(), premakel.begin() + 1);
    auto query = [&](int l, int r){
        ll resr = 0;
        for(int j = 0; j < 31; j++){
            resr += (querya(0, j, l, r) * queryb(1, j, r + 1, n) % mod + querya(1, j, l, r) * queryb(0, j, r + 1, n) % mod) << j;
            resr %= mod;
        }
        return (premakel[r] - premakel[l - 1] + mod - resr + mod) % mod;
    };
    while(q--){
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }
}  
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) slv();
    return 0;
}