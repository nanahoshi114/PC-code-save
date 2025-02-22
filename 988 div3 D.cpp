#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;
using ll = long long;
void slv(){
    ll n, m, l, p = 0, ans = 0;
    bool flag = 0;
    priority_queue<int> power;
    vector<pair<int, int>> barr;
    cin >> n >> m >> l;
    for(int i = 1, maxr = 0; i <= n; i++){
        int l, r;
        cin >> l >> r;
        if(r - l + 1 <= maxr) continue;
        maxr = max(maxr, r - l + 1);
        barr.push_back(make_pair(l, r - l + 1));
    }
    for(int i = 1, ind = 0; i <= m; i++){
        int l, r;
        cin >> l >> r;
        if(ind >= barr.size() || l >= barr.back().first) continue;
        if(!flag){
            while(ind < barr.size() && l >= barr[ind].first){
                while(p < barr[ind].second){
                    if(power.empty()){
                        flag = 1;
                        break;
                    }
                    p += power.top(); power.pop(); ans++;
                }
                ind++;
            }
        }
        power.push(r);
    }
    while(p < barr.back().second){
        if(power.empty()){
            flag = 1;
            break;
        }
        p += power.top(); power.pop(); ans++;
    }
    if(!flag) cout << ans << '\n';
    else cout << -1 << '\n';
}
signed main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) slv();
    return 0;
}