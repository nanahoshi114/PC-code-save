#include <iostream>
using namespace std;
using ll = long long;
const ll INF = 0xffffffffffff;
ll fl[55][55];
bool dp[55][55][40];
int n, m;
int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            fl[i][j] = INF;
        }
    }
    while(m--){
        int u, v;
        cin >> u >> v;
        fl[u][v] = 1;
        dp[u][v][0] = 1;
    }
    for(int t = 1; t <= 31; t++){
        for(int k = 1; k <= n; k++){
            for(int i = 1; i <= n; i++){
                for(int j = 1; j <= n; j++){
                    dp[i][j][t] |= (dp[i][k][t - 1] & dp[k][j][t - 1]);
                    if(dp[i][j][t]) fl[i][j] = 1;
                }
            }
        }
    }
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                fl[i][j] = min(fl[i][j], fl[i][k] + fl[k][j]);
            }
        }
    }
    cout << fl[1][n];
    return 0;
}