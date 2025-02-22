#include <iostream>
#include <cstring>
#define dpind(x) cnt[x] ? (cnt[x] % 2) : 2
using namespace std;
using ull = unsigned long long;
using ll = long long;
int num[30], cnt[10];
ll dp[20][3][3][3][3][3][3][3][3][3][3];
ll dfs(int pos, bool isPrefix0, bool flag){
    if(pos == -1){
        for(int i = 0; i <= 9; i++){
            if(cnt[i] && !((i % 2) ^ (cnt[i] % 2))){
                return 0;
            }
        }
        return 1;
    }
    if(!flag && !isPrefix0 && ~dp[pos][dpind(0)][dpind(1)][dpind(2)][dpind(3)][dpind(4)][dpind(5)][dpind(6)][dpind(7)][dpind(8)][dpind(9)]){
        return dp[pos][dpind(0)][dpind(1)][dpind(2)][dpind(3)][dpind(4)][dpind(5)][dpind(6)][dpind(7)][dpind(8)][dpind(9)];
    }
    int up = flag ? num[pos] : 9;
    ll res = 0;
    for(int i = 0; i <= up; i++){
        cnt[i] += (i != 0 || !isPrefix0) ? 1 : 0;
        res += dfs(pos - 1, isPrefix0 && i == 0, flag && i == num[pos]);
        cnt[i] -= (i != 0 || !isPrefix0) ? 1 : 0;
    }
    if(!flag && !isPrefix0)
        dp[pos][dpind(0)][dpind(1)][dpind(2)][dpind(3)][dpind(4)][dpind(5)][dpind(6)][dpind(7)][dpind(8)][dpind(9)] = res;
    return res;
}
ll work(ull x){
    int cnt = 0;
    while(x){
        num[cnt++] = x % 10;
        x /= 10;
    }
    return dfs(cnt - 1, 1, 1);
}
void slv(){
    ull l, r;
    cin >> l >> r;
    cout << work(r) - work(l - 1) << '\n';
}
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    memset(dp, -1, sizeof(dp));
    int t = 1;
    cin >> t;
    while(t--) slv();
    return 0;
}