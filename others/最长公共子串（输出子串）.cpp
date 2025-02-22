#include <iostream>
#include <string>
using namespace std;
int dp[3005][3005];
int pre[3005][3005];
void rollBack(int x, int y, const string &s1){
    if(x <= 0 || y <= 0) return;
    if(pre[x][y] == 3){
        rollBack(x - 1, y - 1, s1);
        cout << s1[x];
    }else if(pre[x][y] == 1){
        rollBack(x - 1, y, s1);
    }else{
        rollBack(x, y - 1, s1);
    }
}
int main(){ 
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    string s1, s2;
    cin >> s1 >> s2;
    int len1 = s1.size(), len2 = s2.size();
    s1 = " " + s1; s2 = " " + s2;
    for(int i = 1; i <= len1; i++){
        if(s1[i] == s2[1]){
            dp[i][1] = 1;
            pre[i][1] = 3;
        }else{
            dp[i][1] = dp[i - 1][1];
            pre[i][1] = 1;
        }
    }
    for(int i = 1; i <= len2; i++){
        if(s1[1] == s2[i]){
            dp[1][i] = 1;
            pre[1][i] = 3;
        }else{
            dp[1][i] = dp[1][i - 1];
            pre[1][i] = 2;
        }
    }
    for(int i = 2; i <= len1; i++){
        for(int j = 2; j <= len2; j++){
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            pre[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? 1 : 2;
            if(s1[i] == s2[j]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
                pre[i][j] = 3;
            }
        }
    }
    rollBack(len1, len2, s1);
    return 0;
}