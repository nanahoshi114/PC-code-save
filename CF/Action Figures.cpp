#include <iostream>
#define int long long
using namespace std;
const int M = 4e5 + 5;
int n, need, ans;
char c;
bool flag[M], is_buy[M];
void slv(){
    need = ans = 0;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> c;
        flag[i] = (c == '1') ? 1 : 0;
    }
    for(int i = n; i >= 1; i--){
        if(flag[i]){
            if(need + 1 < i){
                need++;
                is_buy[i] = 0;
            }else{
                need--;
                is_buy[i] = 1;
            }
        }else{
            if(need) need--;
            is_buy[i] = 1;
        }
    }
    for(int i = 1; i <= n; i++){
        if(is_buy[i]) ans += i;
    }
    cout << ans << '\n';
}
signed main(){
    int t;
    cin >> t;
    while(t--) slv();
    return 0;
}