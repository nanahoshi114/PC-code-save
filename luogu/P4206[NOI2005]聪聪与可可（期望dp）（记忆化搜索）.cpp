#include <iostream>
#include <cstring>
#include <queue>
#include <bitset>
#include <iomanip>
using namespace std;
using ll = long long;
const int M = 2e3 + 5;
struct Edge{
    int to, next;
}edge[M];
struct Node{
    int pos, dis;
    bool operator<(Node r) const{
        return dis > r.dis;
    }
};
int head[M], cnt, dis[M][M], nextPos[M][M], ent[M];
double dp[M][M];
bitset<M> vis[M];
void add(int u, int v){
    edge[cnt] = {v, head[u]};
    head[u] = cnt++;
}
void dijk(int *dis, int st, bitset<M> &vis){
    priority_queue<Node> pq;
    pq.push({st, 0});
    dis[st] = 0;
    while(!pq.empty()){
        auto now = pq.top();
        pq.pop();
        if(vis[now.pos]) continue;
        vis[now.pos] = 1;
        for(int i = head[now.pos]; ~i; i = edge[i].next){
            Node next = {edge[i].to, now.dis + 1};
            if(next.dis < dis[next.pos]){
                dis[next.pos] = next.dis;
                if(!vis[next.pos]) pq.push(next);
            }
        }
    }
}
double dfs(int now, int to){
    if(dp[now][to] != 0) return dp[now][to];
    if(now == to){
        dp[now][to] = 0;
        return 0;
    }
    int first = nextPos[now][to];
    int second = nextPos[first][to];
    if(first == to || second == to){
        dp[now][to] = 1.0;
        return 1.0;
    }
    for(int i = head[to]; ~i; i = edge[i].next){
        dp[now][to] += dfs(second, edge[i].to) + 1;
    }
    dp[now][to] += dfs(second, to) + 1;
    return dp[now][to] /= (ent[to] + 1);
}
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int N, E, s, t;
    memset(head, -1, sizeof(head));
    memset(dis, 0x7f, sizeof(dis));
    //memset(nextPos, 0x7f, sizeof(nextPos));
    cin >> N >> E;
    cin >> s >> t;
    for(int i = 1, u, v; i <= E; i++){
        cin >> u >> v;
        add(u, v);
        add(v, u);
        ent[u]++; ent[v]++;
    }
    for(int i = 1; i <= N; i++){
        dijk(dis[i], i, vis[i]);
    }
    auto cmpPoint = [&](int t, int posx, int posy){
        if(dis[posx][t] != dis[posy][t]){
            return dis[posx][t] < dis[posy][t];
        }
        return posx < posy;
    };
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(i == j) nextPos[i][i] = i;
            else{
                int minPos = i;
                for(int k = head[i]; ~k; k = edge[k].next){
                    if(cmpPoint(j, edge[k].to, minPos)){
                        minPos = edge[k].to;
                    }
                }
                nextPos[i][j] = minPos;
            }
        }
    }
    cout << fixed << setprecision(3) << dfs(s, t);
    return 0;
}