#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;
const int M = 1e5 + 5;
struct Edge{
    int to, next;
};
struct Node{
    int pre, now;
};
vector<int> head;
vector<Edge> edge;
vector<bool> vis;
void add(int u, int v){
    edge.push_back({v, head[u]});
    head[u] = edge.size() - 1;
}
int bfs(int st){
    if(vis[st]) return 1;
    queue<Node> que;
    que.push({0, st});
    while(!que.empty()){
        Node now = que.front();
        que.pop();
        if(vis[now.now]){
            return 0;
        }
        vis[now.now] = 1;
        for(int i = head[now.now]; ~i; i = edge[i].next){
            if(edge[i].to == now.pre) continue;
            if(vis[edge[i].to]){
                return 0;
            }
            que.push({now.now, edge[i].to});
        }
    }
    return 1;
}
int main(){
    int u, v, st;
    while(1){
        unordered_set<int> uset;
        cin >> u >> v;
        if(u == -1) return 0;
        head.assign(M, -1);
        edge.clear();
        vis.assign(M, 0);
        st = u;
        while(u){
            uset.insert(u); uset.insert(v);
            add(u, v);
            add(v, u);
            cin >> u >> v;
        }
        bool flag = bfs(st);
        if(flag){
            for(auto i : uset){
                if(!vis[i]){
                    flag = 0;
                    break;
                }
            }
        }
        cout << flag << '\n';
    }
    return 0;
}