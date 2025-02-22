#include <iostream>
using namespace std;
using ll = long long;
struct Node{
    int val, w, m;
}arr[105];
ll dp[40005];
int main(){ 
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n, W;
    cin >> n >> W;
    for(int i = 1; i <= n; i++){
        cin >> arr[i].val >> arr[i].w >> arr[i].m;
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++){
        int leave = arr[i].m;
        for(int j = 1; j <= leave; j <<= 1){
            for(int k = W; k >= j * arr[i].w; k--){
                dp[k] = max(dp[k], dp[k - j * arr[i].w] + j * arr[i].val);
                ans = max(ans, dp[k]);
            }
            leave -= j;
        }
        if(leave > 0){
            for(int k = W; k >= leave * arr[i].w; k--){
                dp[k] = max(dp[k], dp[k - leave * arr[i].w] + leave * arr[i].val);
                ans = max(ans, dp[k]);
            }
        }
    }
    cout << ans;
    return 0;
}