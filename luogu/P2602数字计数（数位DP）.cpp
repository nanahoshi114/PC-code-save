#include <iostream>
#include <cstring>
using namespace std;
using ll = unsigned long long;
ll dp[20][20];
int a[15];
ll dfs(int pos, bool flag, bool isPrefix0, ll sum, int num){
    if(pos == 0) return sum;
    if(!flag && !isPrefix0 && ~dp[pos][sum]){
        return dp[pos][sum];
    }
    ll res = 0;
    int up = flag ? a[pos] : 9;
    for(int i = 0; i <= up; i++){
        res += dfs(pos - 1, flag && i == a[pos], isPrefix0 && i == 0, sum + (num == i && (i != 0 || !isPrefix0)), num);
    }
    if(!flag && !isPrefix0){
        dp[pos][sum] = res;
    }
    return res;
}
void work(ll x, ll *cnt){
    int len = 0;
    while(x){
        a[++len] = x % 10;
        x /= 10;
    }
    for(int i = 0; i <= 9; i++){
        memset(dp, -1, sizeof(dp));
        cnt[i] = dfs(len, 1, 1, 0, i);
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    memset(dp, -1, sizeof(dp));
    ll l, r;
    cin >> l >> r;
    ll lcnt[10] = {}, rcnt[10] = {};
    work(r, rcnt); work(l - 1, lcnt);
    for(int i = 0; i <= 9; i++){
        cout << rcnt[i] - lcnt[i] << ' ';
    }
    return 0;
}