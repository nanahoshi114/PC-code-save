#include<iostream>
#include <map>
#include <utility>
#include <queue>
#include<algorithm>
using namespace std;
typedef pair<int,int> position;
typedef queue<position> ryusei;
struct statement{
    int x,y;
    int t;
}now;
int dx[6] = {-1, 0, 1, 0, 0};
int dy[6] = {0, 1, 0, -1, 0};
queue<statement> que;
map<int, ryusei> sta; //<time, ryusei>
int m, tx, ty, tt, maxx = 20, maxy = 20;
bool flag[305][305];
bool is_unsafe[305][305];
bool is_legal(int x, int y){
    return x >= 0 && y >= 0 && !flag[x][y];
}
void mark(int x, int y, bool if_initial){
    for(int i = 0; i <= 4; i++){
        int ix = x + dx[i];
        int iy = y + dy[i];
        if(is_legal(ix, iy)){
            if(if_initial) is_unsafe[ix][iy] = 1;
            else flag[ix][iy] = 1;
        }   
    }
}
void ryusei_fall(int t){
    if(sta.find(t) != sta.end()){
        while(!sta[t].empty()){
            mark(sta[t].front().first, sta[t].front().second, 0);
            sta[t].pop();
        }
    }
}
int bfs(){
    que.push((statement){0, 0, 0});
    flag[0][0] = 1;
    ryusei_fall(0);
    while(!que.empty()){
        now = que.front();
        que.pop();
        if(!is_unsafe[now.x][now.y]){
            return now.t;
        }
        ryusei_fall(now.t + 1);
        for(int i = 0; i <= 3; i++){
            int ix = now.x + dx[i];
            int iy = now.y + dy[i];
            if(is_legal(ix, iy)){
                que.push((statement){ix, iy, now.t + 1});
                flag[ix][iy] = 1;
            }
        }
        
    }
    return -1;
}
int main(){
    cin >> m;
    while(m--){
        cin >> tx >> ty >> tt;
        if(sta.find(tt) == sta.end()){
            sta[tt] = {};
        }
        sta[tt].push(position(tx, ty));
        mark(tx, ty, 1);
    }
    cout << bfs();
    //system("pause");
    return 0;
}