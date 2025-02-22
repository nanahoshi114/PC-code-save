#include <iostream>
#include <queue>
using namespace std;
using ll = unsigned long long;
const int mod = 1e5 + 3;
ll n, k, f[mod], sum;
queue<ll> que;
int main(){
    cin >> n >> k;
    f[1] = sum = 1;
    que.push(f[1]);
    for(int i = 2; i <= k; i++){
        f[i] = (f[i - 1] * 2) % mod;
        sum = sum + f[i];
        que.push(f[i]);
    }
    for(int i = k + 1; i <= n; i++){
        f[i] = sum % mod;
        sum -= que.front();
        que.pop();
        sum += f[i];
        que.push(f[i]);
    }
    cout << f[n];
    return 0;
}
