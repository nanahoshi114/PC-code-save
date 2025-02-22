#include <iostream>
#include <queue>
#include <vector>
#define int long long
using namespace std;
const int INF = 9223372036854775807;
void solve();
struct node{
    int pos, dis, tpt;
    const bool operator<(const node &x)const{
        return ((dis == x.dis) ? (tpt > x.tpt) : (dis > x.dis));
    }
};
struct Edge{
    int to, next, dis;
};
void add(int u, int v, int d, vector<int> &head, vector<Edge> &edge){
    Edge e = {v, head[u], d};
    edge.push_back(e);
    head[u] = edge.size() - 1;
}
int n, m, k, w;
void bfs(vector<int> head, vector<Edge> edge, vector<int> &dis, vector<bool> &vis, vector<int> &teleportTime){
    priority_queue<node> que;
    que.push({1, 0, 0});
    while(!que.empty()){
        node now = que.top();
        que.pop();
        if(vis[now.pos]) continue;
        vis[now.pos] = 1;
        for(int i = head[now.pos]; ~i; i = edge[i].next){
            node next = {edge[i].to, now.dis + edge[i].dis, now.tpt};
            if(next.dis < dis[next.pos] || (next.dis == dis[next.pos] && next.tpt < teleportTime[next.pos])){
                dis[next.pos] = next.dis;
                teleportTime[next.pos] = next.tpt;
                if(!vis[next.pos]){
                    que.push(next);
                }
            }
        }
        for(int i = now.pos - k; i <= now.pos + k && k; i += 2 * k){
            if(1 <= i && i <= n){
                node next = {i, now.dis + w, now.tpt + 1};
                if(next.dis < dis[next.pos] || (next.dis == dis[next.pos] && next.tpt < teleportTime[next.pos])){
                    teleportTime[next.pos] = next.tpt;
                    dis[next.pos] = next.dis;
                    if(!vis[next.pos]){
                        que.push(next);
                    }
                }
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        solve();
    }
    return 0;
}
void solve(){
    cin >> n >> m >> k >> w;
    vector<int> head(n + 1, -1);
    vector<Edge> edge;
    vector<int> dis(n + 1, INF);
    vector<int> teleportTime(n + 1, 0);
    vector<bool> vis(n + 1, 0);
    dis[1] = 0;
    while(m--){
        int u, v, d;
        cin >> u >> v >> d;
        add(u, v, d, head, edge);
        add(v, u, d, head, edge);
    }
    bfs(head, edge, dis, vis, teleportTime);
    if(dis[n] == INF){
        cout << -1 << ' ' << -1;
    }else{
        cout << dis[n] << ' ' << teleportTime[n];
    }
    cout << '\n';
}