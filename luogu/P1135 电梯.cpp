#include <iostream>
#include <queue>
using namespace std;
int n, a, b, k[1000];
bool fp[1000];
struct level{
    int stage, ki;
    int step;
};
queue<level> que;
bool is_legal(level l){
    return (l.stage >= 1 && l.stage <= n) &&( !fp[l.stage]);
}
void bfs(){
    que.push((level){a, k[a], 0});
    fp[a] = 1;
    while(!que.empty()){
        level temp = que.front();
        level next;
        que.pop();
        if(temp.stage == b){
            cout << temp.step;
            return ;
        }
        //cout << temp.stage << ' ' << temp.ki <<' ' << temp.step << endl;
        //if(temp.ki == 0) continue;
        next = (level){temp.stage + temp.ki, k[temp.stage + temp.ki], temp.step + 1};
        if(is_legal(next)){
            que.push(next);
            fp[next.stage] = 1;
        }
        next = (level){temp.stage - temp.ki, k[temp.stage - temp.ki], temp.step + 1};
        if(is_legal(next)){
            que.push(next);
            fp[next.stage] = 1;
        }
    }
    cout << -1;
}
int main(){
    cin >> n >> a >> b;
    for(int i = 1; i <= n; i++){
        cin >> k[i];
    }
    bfs();
	return 0;
}