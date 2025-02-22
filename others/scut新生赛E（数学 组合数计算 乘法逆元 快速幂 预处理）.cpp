#include <iostream>
#include <vector>
#include <array>
using namespace std;
using ll = unsigned long long;
const ll P = 998244353;
ll fastPow(ll a, ll b, ll mod) {
    ll result = 1;
    a = a % mod;
    while (b > 0) {
        if (b & 1) {
            result = (result * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return result;
}
vector<ll> pret(2, 1);
array<ll, int(2e5) + 5> inv;
vector<ll> pres{1, 2};
void make(ll n){
    if(pret.size() - 1 >= n) return;
    for(ll i = pret.size(); i <= n; i++){
        pret.push_back((i * pret.back()) % P);
        pres.push_back((pres.back() << 1) % P);
    }
    inv[n] = fastPow(pret[n], P - 2, P);
    for(ll i = n - 1; i >= 0 && !inv[i]; i--){
        inv[i] = inv[i + 1] * (i + 1) % P;
    }
}
ll C(ll n, ll m){
    if(m == 0) return 1;
    return (((pret[n] * inv[m]) % P) * inv[n - m]) % P;
}
void slv(){
    int n, m;
    cin >> n >> m;
    make(n);
    ll sum = 0;
    for(int i = max(0, m - n); i <= m / 2; i++){
        sum += (((C(n, i) * C(n - i, m - 2 * i)) % P) * pres[m - 2 * i]) % P;
    }
    cout << sum % P << '\n';
}
int main(){
    int t;
    cin >> t;
    while(t--) slv();
    return 0;
}