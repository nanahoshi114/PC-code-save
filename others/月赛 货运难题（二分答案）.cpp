#include <iostream>
using namespace std;
const int M = 1e6 + 5;
using ll = long long;
void solve();
ll n, k, a[M], l, r;
bool is_legal(ll x){
    ll ts = 0, d= 0;
    for(int i = 1; i <= n; i++){
        if(ts + a[i] > x){
            d++;
            ts = a[i];
        }else{
            ts += a[i];
        }
        if(d > k) return 0;
    }
    d++;
    if(d <= k) return 1;
    else return 0;
}
int main(){
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
void solve(){
    l = r = 0;
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        l = max(l, a[i]);
        r += a[i];
    }
    ll mid = 0;
    while(l < r){
        mid = (l + r) / 2;
        if(is_legal(mid)){
            r = mid;
        }else{
            l = mid + 1;
        }
    }
    cout << l << endl;
    
}