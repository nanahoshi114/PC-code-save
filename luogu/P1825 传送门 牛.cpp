#include <iostream>
#include <cctype>
#include <map>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;
typedef pair<int, int> position;
bool flag[100], m_flag[301][301];
int n, m, min_count = 999999;
char s[301][301];
position arr[100];
map<position, position> tp;
struct point{
    position ind;
    int step;
}st_p, tmp;
queue<point> que;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
void teleport(int &x, int &y){
    position temp = tp[position(x, y)];
    x = temp.first;
    y = temp.second;
}
bool is_legal(position p){
    int x = p.first, y = p.second;
    return x >= 0 && y >= 0 && x < n && y < m && s[x][y] != '#' && (!m_flag[x][y]);
}
void bfs(){
    que.push(st_p);
    while(!que.empty()){
        tmp = que.front();
        que.pop();
        int x = tmp.ind.first, y = tmp.ind.second;
        if(isupper(s[x][y])){
            teleport(x, y);
        }
        if(s[x][y] == '='){
            //min_count = min(tmp.step, min_count);
            cout << tmp.step;
            break;
        }
        for(int i = 0; i < 4; i++){
            position next = position(x + dx[i], y + dy[i]);
            if(is_legal(next)){ 
                m_flag[next.first][next.second] = 1;
                que.push((point){next, tmp.step + 1});
            }
        }
        
    }
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >>s[i][j];
            if(s[i][j] == '@'){
                st_p.ind.first = i, st_p.ind.second = j;
                st_p.step = 0;
            }
            if(isupper(s[i][j])){
                if(flag[s[i][j]]){
                    tp[position(i, j)] = arr[s[i][j]];
                    tp[arr[s[i][j]]] = position(i, j);
                }else{
                    arr[s[i][j]] = position(i, j);
                    flag[s[i][j]] = 1;
                }
            }
        }
    }
    bfs();
    //cout << min_count;
	return 0;
}