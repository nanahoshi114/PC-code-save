#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <bitset>
using namespace std;
using ll = long long;
const int M = 3e4 + 5;

struct Edge{
    int to, next;
};
array<Edge, M> edge;
array<int, M> head, ent, ans;
array<bitset<M>, M> mp;
int cnt;
void add(int u, int v){
    edge[cnt] = {v, head[u]};
    head[u] = cnt++;
}
void topo(int n){
    queue<int> S;
    for(int i = 1; i <= n; i++){
        if(!ent[i]){
            mp[i].set(i);
            S.push(i);
        }
    }
    while(!S.empty()){
        int now = S.front();
        S.pop();
        mp[now].set(now);
        ans[now] = mp[now].count();
        for(int i = head[now]; ~i; i = edge[i].next){
            mp[edge[i].to] |= mp[now];
            if(!--ent[edge[i].to]){
                S.push(edge[i].to);
            }
        }
    }   
}
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n, m, x, y;
    cin >> n >> m;
    head.fill(-1);
    for(int i = 1; i <= m; i++){
        cin >> x >> y;
        add(y, x);
        ent[x]++;
    }
    topo(n);
    for(int i = 1; i <= n; i++){
        cout << ans[i] << '\n';
    }
    return 0;
}