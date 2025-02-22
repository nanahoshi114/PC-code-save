#include <iostream>
#include <queue>
using namespace std;
int a[100005];
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    priority_queue<int> L;
    priority_queue<int, vector<int>, greater<int>> S;
    S.push(a[1]);
    cout << a[1] << '\n';
    for(int i = 2; i <= n; i++){
        if(a[i] > S.top()) S.push(a[i]);
        else L.push(a[i]);
        if(i & 1){
            while(S.size() != L.size() + 1){
                if(S.size() > L.size()){
                    L.push(S.top());
                    S.pop();
                }else{
                    S.push(L.top());
                    L.pop();
                }
            }
            cout << S.top() << '\n';
        }
    }

    return 0;
}