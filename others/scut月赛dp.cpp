#include <iostream>
#include <array>
#include <algorithm>
using namespace std;
array<int, 20> a{};
array<array<int, 3>, 20> dp{};
//dp[i][0]�޷��� dp[i][1]����ĵ�һ�ι��� dp[i][2]����ĵڶ��ι���
int n;
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    dp[1][0] = a[1];
    dp[2][0] = a[1] + a[2];
    dp[2][1] = a[1];
    for(int i = 3; i <= n; i++){
        dp[i][0] = min(dp[i - 1][0] + a[i], dp[i - 1][2] + a[i]);
        dp[i][1] = dp[i - 1][0];
        dp[i][2] = dp[i - 1][1];
    }
    cout << min({dp[n][0], dp[n][1], dp[n][2]}) + 1;
    return 0;
}