#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
ll fastPow(ll a, ll b){
    ll res = 1;
    while(b){
        if(b & 1){
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
class Comb{
    vector<ll> inv;
    vector<ll> prev;
public:
    explicit Comb(int size) : inv(size + 1), prev(size + 1){
        prev[0] = prev[1] = 1;
        for(int i = 2; i <= size; i++){
            prev[i] = prev[i - 1] * i % mod;
        }
        inv[size] = fastPow(prev[size], mod - 2);
        for(int i = size - 1; i >= 0; i--){
            inv[i] = inv[i + 1] * (i + 1) % mod;
        }
    }
    ll operator()(ll n, ll m){
        if(m == 0) return 1;
        return (prev[n] * inv[m] % mod) * inv[n - m] % mod;
    }
};
Comb C(2e5);
ll preqp[100005];
void slv(){
    ll n, p, q;
    cin >> n >> p >> q;
    ll ans = 0, invq = fastPow(fastPow(q, n), mod - 2);
    ll tans = (fastPow(p, n) * invq) % mod; invq = (invq * q) % mod;
    preqp[0] = 1;
    for(int i = 1; i < n; i++){
        preqp[i] = preqp[i - 1] * (q - p) % mod;
    }
    for(int i = n - 1; i >= 0; i--){
        ans = (ans + ((C(n - 1 + i, i) * preqp[i] % mod) * invq % mod)) % mod;
        invq = (invq * q) % mod;
    }
    cout << (tans * ans) % mod << '\n';
}
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) slv();    
    return 0;
}