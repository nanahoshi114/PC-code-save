#include <iostream>
#include <array>
#include <algorithm>
#include <cmath>
#include <numeric>
using namespace std;
using ll = long long;
using lb = long double;
const int M = 1e5 + 5;
array<int, M> a, b;
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++){
        cin >> b[i];
    }
    sort(a.begin() + 1, a.begin() + 1 + n);
    sort(b.begin() + 1, b.begin() + 1 + n);
    auto check = [n](lb x){
        ll cnt = 0;
        for(int i = 1, j = 1; i <= n; i++){
            while(lb(a[j]) < lb(b[i]) * x && j <= n) j++;
            cnt += j - 1;
        }
        return cnt;
    };
    while(q--){
        ll c;
        cin >> c;
        lb l = lb(a[1]) / b[n], r = lb(a[n]) / b[1], mid;
        while(r - l >= 1e-13){
            mid = (l + r) / 2;
            if(check(mid) >= c){
                r = mid;
            }else{
                l = mid;
            }
        }
        for(int i = 1, j = 1; i <= n; i++){
            while(j <= n && lb(a[i]) > lb(b[j]) * r && fabs(lb(a[i]) - lb(b[j]) * r) > 1e-7) j++;
            if(fabs(lb(a[i]) / lb(b[(j > n) ? n : j]) - r) <= 1e-13){
                int t = gcd(a[i], b[j]);
                cout << a[i] / t << ' ' << b[j] / t << '\n';
                break;
            }
        }
    }
    return 0;
}