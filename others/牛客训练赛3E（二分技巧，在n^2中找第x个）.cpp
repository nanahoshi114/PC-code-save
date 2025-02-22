#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
using ll = long long;
void slv(){
    int n;
    ll k;
    cin >> n >> k;
    vector<double> left, right;
    for(int i = 1, p, v; i <= n; i++){
        cin >> p >> v;
        if(v == 1) left.push_back(p);
        else right.push_back(p);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    auto check = [&](double x){
        ll cnt = 0;
        for(int i = 0; i < left.size(); i++){
            auto it = lower_bound(right.begin(), right.end(), 2 * x + left[i]);
            auto rightbegin = lower_bound(right.begin(), right.end(), left[i]);
            cnt += it - rightbegin;
        }
        return cnt;
    };
    double l = 0, r = 1e10;
    while(r - l >= 1e-7){
        double mid = (l + r) / 2;
        if(check(mid) > k - 1){
            r = mid;
        }else{
            l = mid;
        }
    }
    if(r == 1e10){
        cout << "No\n";
    }else{
        cout << "Yes\n";
        cout << fixed << setprecision(6) << r << '\n';
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) slv();
    return 0;
}