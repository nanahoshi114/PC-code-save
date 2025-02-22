#include <iostream>
#include <queue>
using namespace std;
using ll = long long;
ll strk, map[1005][1005], ans;
bool vis[1005][1005];
int dx[5] = {1, 0, -1, 0}, dy[5] = {0, 1, 0, -1};
int n, m, sx, sy;
struct Node{
    int x, y;
    const bool operator<(Node r) const {
        return map[x][y] > map[r.x][r.y];
    }
    bool legal(){
        return x >= 1 && y >= 1 && x <= n && y <= m && !vis[x][y];
    }
};
void bfs(){
    vis[sx][sy] = 1;
    priority_queue<Node> que;
    que.push({sx, sy});
    strk = map[sx][sy];
    while(!que.empty()){
        Node now = que.top();
        que.pop();
        if(strk < map[now.x][now.y]){
            ans += map[now.x][now.y] - strk;
            strk = map[now.x][now.y];
        }
        if(now.x != sx || now.y != sy) strk += map[now.x][now.y];
        for(int i = 0; i < 4; i++){
            Node next = {now.x + dx[i], now.y + dy[i]};
            if(next.legal()){
                vis[next.x][next.y] = 1;
                que.push(next);
            }
        }
    }
}
int main(){
    cin >> n >> m >> sx >> sy;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> map[i][j];
        }
    }
    bfs();
    if(ans == 0){
        cout << "No cheating need.";
    }else{
        cout << map[sx][sy] + ans;
    }
    return 0;
}