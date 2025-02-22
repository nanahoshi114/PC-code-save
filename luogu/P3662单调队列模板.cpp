#include <iostream>
#include <queue>
using namespace std;
const int M = 1e5 + 5;
bool flag[M];
queue<bool> que;
int n, k, b, tsum, ans = 1e6;
int main(){
    cin >> n >> k >> b;
    while(b--){
        int t;
        cin >> t;
        flag[t] = 1;  
    }
    for(int i = 1; i <= k; i++){
        que.push(flag[i]);
        tsum += (int)flag[i];
    }
    ans = tsum;
    for(int i = k + 1; i <= n; i++){
        que.push(flag[i]);
        tsum = tsum + (int)flag[i] - (int)que.front();
        que.pop();
        ans = min(tsum, ans);
    }
    cout << ans;
    return 0;
}