#include <iostream>
#include <numeric>
#include <cstring>
#include <climits>
using namespace std;
int dp[205][205], arr[205];
int main(){ 
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n;
    cin >> n;
    memset(dp, 0x7f, sizeof(dp));
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
        dp[i][i] = 0;
    }
    for(int i = 1; i <= n; i++){
        arr[i + n] = arr[i];
        dp[i + n][i + n] = 0;
    }
    partial_sum(arr + 1, arr + 1 + 2 * n, arr + 1);
    for(int l = 1; l <= n; l++){
        for(int i = 1; i + l - 1 <= 2 * n; i++){
            int end = i + l - 1;
            for(int j = i; j < end; j++){
                dp[i][end] = min(dp[i][end], dp[i][j] + dp[j + 1][end] + arr[end] - arr[i - 1]);
            }
        }
    }
    int ans = INT_MAX;
    for(int i = 1; i + n - 1 <= 2 * n; i++){
        ans = min(ans, dp[i][i + n - 1]);
    }
    cout << ans << '\n';
    memset(dp, 0, sizeof(dp));
    for(int l = 1; l <= n; l++){
        for(int i = 1; i + l - 1 <= 2 * n; i++){
            int end = i + l - 1;
            for(int j = i; j < end; j++){
                dp[i][end] = max(dp[i][end], dp[i][j] + dp[j + 1][end] + arr[end] - arr[i - 1]);
            }
        }
    }
    ans = 0;
    for(int i = 1; i + n - 1 <= 2 * n; i++){
        ans = max(ans, dp[i][i + n - 1]);
    }
    cout << ans << '\n';
    return 0;
}