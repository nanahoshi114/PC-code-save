#include <iostream>
#include <vector>
#include <queue>
using namespace std;
using ll = long long;
const int M = 1e5 + 5;
struct Edge{
    int to, next;
};
struct Node{
    int pos;
    ll dis;
};
vector<Edge> edge;
vector<int> head;
ll a[M];
vector<int> ent;
int n, m;
void add(int u, int v){
    edge.push_back({v, head[u]});
    head[u] = edge.size() - 1;
}
ll getdis(ll strk, int to){
    if(strk >= a[to]) return strk + a[to];
    else return strk - (a[to] - strk);
}
bool check(ll x){
    vector<int> tent(ent);
    queue<int> S;
    vector<ll> maxstrk(n + 1, -2e10);
    for(int i = 1; i <= n; i++){
        if(!tent[i]){
            S.push(i);
            maxstrk[i] = max(maxstrk[i], getdis(x, i));
        }
    }
    while(!S.empty()){
        int now = S.front();
        S.pop();
        for(int i = head[now]; ~i; i = edge[i].next){
            int to = edge[i].to;
            maxstrk[to] = max(maxstrk[to], getdis(maxstrk[now], to));
            if(!(--tent[to])){
                S.push(to);
            }
        }
    }
    return maxstrk[n] > 0;
}
int main(){ 
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    cin >> n >> m;
    head.assign(n + 1, -1);
    ent.assign(n + 1, 0);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1, u, v; i <= m; i++){
        cin >> u >> v;
        add(u, v);
        ent[v]++;
    }
    ll l = 1, r = 2e10 + 1, mid;
    while(l < r){
        mid = (l + r) >> 1;
        if(check(mid)){
            r = mid;
        }else{
            l = mid + 1;
        }
    }
    cout << r;
    return 0;
}