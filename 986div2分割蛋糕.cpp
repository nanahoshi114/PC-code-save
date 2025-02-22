#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using ll = long long;
ll n, m, v, a[int(2e5) + 5], psum[int(2e5) + 5], ans, tot;
ll get_sum(ll l, ll r){
    return psum[r] - psum[l - 1];
}
void slv(){
    ans = tot = 0;
    cin >> n >> m >> v;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        tot += a[i];
    }
    partial_sum(a + 1, a + 1 + n, psum + 1);
    vector<ll> pa, rpa;
    pa.push_back(0); rpa.push_back(n + 1);
    for(int i = 1, sum = 0; i <= n; i++){
        sum += a[i];
        if(sum >= v){
            pa.push_back(i);
            sum = 0;
        }
    }
    if(pa.size() - 1 < m){
        cout << -1 << '\n';
        return ;
    }
    for(int i = n, sum = 0; i >= 1; i--){
        sum += a[i];
        if(sum >= v){
            rpa.push_back(i);
            sum = 0;
        }
    }
    for(int i = 1; i <= m + 1; i++){
        ans = max(ans, tot - get_sum(1, pa[i - 1]) - get_sum(rpa[m + 1 - i], n));
    }
    cout << ans << '\n';
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) slv();
    return 0;
}