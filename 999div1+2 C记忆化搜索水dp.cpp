#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
using ll = long long;
const ll mod = 998244353;
int a[200005], n;
unordered_map<int, unordered_map<int, ll>> dp[2];
ll dfs(int pos, int lnum, bool preFlag){
    if(pos == n + 1){
        return 1;
    }
    if(dp[preFlag].find(pos) != dp[preFlag].end()){
        if(dp[preFlag][pos].find(lnum) != dp[preFlag][pos].end()){
            return dp[preFlag][pos][lnum];
        }
    }
    ll res = 0;
    if(!preFlag)
        res = (res + dfs(pos + 1, lnum + 1, 1)) % mod;
    if(lnum == a[pos])
        res = (res + dfs(pos + 1, lnum, 0)) % mod;
    dp[preFlag][pos][lnum] = res;
    return res;
}
void slv(){
    dp[0].clear();
    dp[1].clear();
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    cout << dfs(1, 0, 0) << '\n';
}
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) slv();
    return 0;
}