#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
using namespace std;
const int MAXN = 2e5 + 5;
int n, k, ans;
int a[MAXN];
vector<pair<int, int>/*num, length*/> vec;
void solve();
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }    
    return 0;
}
void solve(){
    ans = 0;
    vec.clear();
    queue<pair<int, int>> que;
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    sort(a + 1, a + 1 + n);
    int last = a[1], lastn = 1;
    for(int i = 2; i <= n; i++){
        if(a[i] != last){
            vec.push_back(make_pair(last, lastn));
            last = a[i];
            lastn = 1;
        }else lastn++;
    }
    vec.push_back(make_pair(last, lastn));
    que.push(vec[0]);
    int ts = vec[0].second; ans = ts;
    for(auto i = vec.begin() + 1; i != vec.end(); i++){
        if(i->first - que.back().first == 1){
            que.push(*i);
            ts += i->second;
            if(que.size() > k){
                ts -= que.front().second;
                que.pop();
            }
        }else{
            while(que.size()) que.pop();
            que.push(*i);
            ts = i->second;
        }
        ans = max(ans, ts);
    }
    cout << ans << endl;

}