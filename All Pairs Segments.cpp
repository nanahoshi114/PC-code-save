#include <iostream>
#include <map>
#define ll long long
using namespace std;
ll n, q, l, r, i, tx, ty, last;
map<ll, ll> ma; // <k, pm>
void solve(){
    ma.clear();
    last = 0;
    cin >> n >> q;
    cin >> l;
    for(i = 2, tx = n - 1, ty = 1; i <= n; i++, tx--, ty++, l = r){
        cin >> r;
        ma[last + tx]++;
        last = tx * ty;
        ma[tx * ty] += r - l - 1;
    }
    ma[n - 1]++;
    while(q--){ 
        ll k;
        cin >> k;
        cout << ma[k] << ' ';
    }
    cout << '\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}