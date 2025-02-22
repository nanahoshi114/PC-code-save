#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;
ll n, a[2005], ans, l, r, mid;
bool check(ll x){
    bool flag = 0;
    for(int i = 2; i <= n; ){
        if(a[i] - a[i - 1] > x){
            if(flag) return 0;
            else{
                flag = 1;
                i++;
            }
        }else{
            i += 2;
        }
    }
    return 1;
}
void slv(){
    l = 1e15, r = 0;
    ans = 0;
    cin >> n;
    cin >> a[1];
    if(n == 1){
        cout << 1 << '\n';
        return ;
    }
    for(int i = 2; i <= n; i++){
        cin >> a[i];
        l = min(a[i] - a[i - 1], l);
        r = max(a[i] - a[i - 1], r);
    }
    if(!(n & 1)){
        for(int i = 2; i <= n; i += 2){
            ans = max(ans, a[i] - a[i - 1]);
        }
    }else{
        while(l < r){
            mid = (l + r) / 2;
            if(check(mid)){
                r = mid;
            }else{
                l = mid + 1;
            }
        }
        ans = l;
    }
    cout << ans << '\n';
}
int main(){
    int t;
    cin >> t;
    while(t--) slv();
    return 0;
}