#include <iostream>
#include <cstring>
using namespace std;
const int INF = 0x7f7f7f7f;
int dp[1 << 11];
int opt[105][15];
int n, m;
void dfs(int now, int step){
    if(dp[now] <= step) return ;
    dp[now] = step;
    if(now == 0) return ;
    for(int i = 1; i <= m; i++){
        int next = now;
        for(int j = 1; j <= n; j++){
            if(opt[i][j] == 1 && (now & (1 << (j - 1))) || opt[i][j] == -1 && (!(now & (1 << (j - 1))))){
                next ^= (1 << (j - 1));
            }
        }
        dfs(next, step + 1);
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    memset(dp, 0x7f, sizeof(dp));
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            cin >> opt[i][j];
        }
    }
    dfs((1 << n) - 1, 0);
    cout << ((dp[0] == INF) ? -1 : dp[0]);
    return 0;
}