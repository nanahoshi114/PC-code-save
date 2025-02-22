#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
const int M = 2e5 + 5;
array<int, M> a, b;
void slv(){
    int n, k;
    cin >> n >> k;
    vector<int> check_num;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        check_num.push_back(a[i]);
    }
    for(int i = 1; i <= n; i++){
        cin >> b[i];
        check_num.push_back(b[i]);
    }
    sort(a.begin() + 1, a.begin() + 1 + n);
    sort(b.begin() + 1, b.begin() + 1 + n);
    sort(check_num.begin(), check_num.end());
    long long ans = 0;
    for(int i = 0; i < check_num.size(); i++){
        if(i != 0 && check_num[i] == check_num[i - 1]) continue;
        auto it = lower_bound(b.begin() + 1, b.begin() + 1 + n, check_num[i]);
        auto itg = lower_bound(a.begin() + 1, a.begin() + 1 + n, check_num[i]);
        int bn = (b.begin() + 1 + n - it) - (a.begin() + 1 + n - itg);
        if(bn > k) continue;
        ans = max(ans, (long long)(b.begin() + 1 + n - it) * check_num[i]);
    }
    cout << ans << '\n';
}
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--) slv();
    return 0;
}