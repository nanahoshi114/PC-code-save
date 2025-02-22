#include <iostream>
#include <queue>
#include <vector>
#include <array>
using namespace std;
struct Num{
    vector<int> pl;
    vector<int> mi;
};
array<Num, int(2e5) + 5> a;
array<int, int(2e5) + 5> flag;
int n, q;
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= q; i++){
        int l, r, x;
        cin >> l >> r >> x;
        a[l].pl.push_back(x);
        a[r + 1].mi.push_back(x);
    }
    priority_queue<int> que;
    que.push(0); flag[0] = 1;
    for(int i = 1; i <= n; i++){
        for(auto j : a[i].pl){
            que.push(j);
            flag[j]++;
        }
        for(auto j : a[i].mi){
            if(que.top() == j) que.pop();
            flag[j]--;
        }
        while(!flag[que.top()]){
            que.pop();
        }
        cout << que.top() << ' ';
    }
    return 0;
}

