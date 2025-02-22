#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
struct Node{
    int w, v;
};
ll dp[105][1005];
int main(){ 
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    vector<vector<Node>> vec;
    int m, n;
    cin >> m >> n;
    for(int i = 1, a, b, c; i <= n; i++){
        cin >> a >> b >> c;
        if(vec.empty() || vec.size() - 1 < c) vec.resize(c + 1, vector<Node>());
        vec[c].push_back({a, b});
    }
    ll ans = 0;
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= vec.size() - 1; j++){
            for(Node &k : vec[j]){
                if(i - k.w >= 0){
                    dp[j][i] = max(dp[j - 1][i - k.w] + k.v, dp[j][i]);
                    ans = max(ans, dp[j][i]);
                }
            }
        }
    }
    cout << ans;
    return 0;
}