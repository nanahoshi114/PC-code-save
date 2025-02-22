#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;
const int M = 6e3 + 5;
struct Edge{
    int to, next;
}edge[M];
int val[M], cnt, head[M], dp[M][2], fatherCount[M], ans = INT_MIN;
void add(int u, int v){
    edge[cnt] = {v, head[u]};
    head[u] = cnt++;
}
void work(int now){
    dp[now][1] = val[now];
    dp[now][0] = 0;
    if(head[now] == -1){
        return ;
    }
    for(int i = head[now]; ~i; i = edge[i].next){
        int next = edge[i].to;
        work(next);
        dp[now][0] += max(dp[next][0], dp[next][1]);
        dp[now][1] += dp[next][0];
    }
}
int main(){ 
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n;
    cin >> n;

    memset(head, -1, sizeof(int) * (n + 5));
    for(int i = 1; i <= n; i++){
        cin >> val[i];
    }
    for(int i = 1, u, v; i <= n - 1; i++){
        cin >> v >> u;
        add(u, v);
    }
    for(int i = 0; i < cnt; i++){
        fatherCount[edge[i].to]++;
    }
    for(int i = 1; i <= n; i++){
        if(!fatherCount[i]){
            work(i);
            ans = max({ans, dp[i][1], dp[i][0]});
        }
    }
    cout << ans;
    return 0;
}