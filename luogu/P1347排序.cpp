#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct Edge{
    int to, next;
};
vector<int> head;
vector<Edge> edge;
int n;
vector<int> ent, ans;
void add(int u, int v){
    edge.push_back({v, head[u]});
    head[u] = edge.size() - 1;
}
int topo(){
    bool flag = 0;
    vector<int> tent(ent);
    vector<int> tans;
    queue<int> S;
    for(int i = 1; i <= n; i++){
        if(!tent[i]) S.push(i); 
    }
    while(!S.empty()){
        if(S.size() > 1) flag = 1; //if unconcernable
        int now = S.front();
        S.pop();
        for(int i = head[now]; ~i; i = edge[i].next){
            if(!(--tent[edge[i].to])){
                S.push(edge[i].to);
            }
        }
        tans.push_back(now);
    }
    for(int i = 1; i <= n; i++){ //find if cycle
        if(tent[i]){
            return 0;
        }
    }
    //if(tans.size() < n || ds.getcon() > 1) return 2;
    if(flag) return 2;
    ans = tans; 
    return 1; 
}
int main(){
    int q, flag = 0;
    cin >> n >>  q;
    head.assign(30, -1); ent.assign(30, 0);
    for(int i = 1; i <= q; i++){
        char a, opt, b;
        cin >> a >> opt >> b;
        a -= 'A' - 1; b -= 'A' - 1;
        add(a, b);
        ent[b]++;
        flag = topo();
        if(flag == 1){
            cout << "Sorted sequence determined after " << i << " relations: ";
            for(auto i : ans){
                cout << char('A' + i - 1);
            }
            cout << '.';
            return 0;            
        }else if(flag == 0){
            cout << "Inconsistency found after " << i << " relations.";  
            return 0;          
        }
    }
    cout << "Sorted sequence cannot be determined.";
    return 0;
}