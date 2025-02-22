#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
struct position{
    double x, y;
    const double operator+(const position r)const{
        return sqrt((x - r.x) * (x - r.x) + (y - r.y) * (y - r.y));
    }
}pos[20];
double min_dist[int(1e5)][20], ans = 2e9;
int n, end_state;
bool vis[20];
void dfs(int now, double length, int state){
    if(length >= min_dist[state][now] && min_dist[state][now] != 0) return;
    min_dist[state][now] = length;
    if(state == end_state){
        ans = min(ans, length);
        return ;
    }
    for(int i = 1; i <= n; i++){
        if(!vis[i]){
            vis[i] = 1;
            dfs(i, length + (pos[now] + pos[i]), state | (1 << (i - 1)));
            vis[i] = 0;
        }
    }
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        end_state = (end_state << 1) + 1;
    }
    for(int i = 1; i <= n; i++){
        cin >> pos[i].x >> pos[i].y;
    }
    for(int i = 1; i <= n; i++){
        vis[i] = 1;
        dfs(i, pos[i] + pos[0], 1 << (i - 1));
        vis[i] = 0;
    }
    cout << fixed << setprecision(2) << ans;
    return 0;
}