#include <iostream>
using namespace std;
using ll = unsigned long long;
const ll mod = 1e5 + 3;
ll n, k, f[100005], tsum[100005];
int main(){
    cin >> n >> k;
    f[1] = tsum[1] = 1;
    for(int i = 2; i <= k; i++){
        f[i] = (f[i - 1] * 2) % mod;
        tsum[i] = tsum[i - 1] + f[i];
    }
    for(int i = k + 1; i <= n; i++){
        f[i] = (tsum[i - 1] - tsum[i - 1 - k]) % mod;
        tsum[i] = tsum[i - 1] + f[i];
    }
    cout << f[n];
    return 0;
}