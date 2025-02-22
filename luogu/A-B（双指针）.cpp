#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using ll = long long;
ll n, c, ans;
vector<ll> vec;
int main(){
    cin >> n >> c;
    while(n--){
        int t;
        cin >> t;
        vec.push_back(t);
    }
    sort(vec.begin(), vec.end());
    for(auto i = vec.begin(), l = vec.begin(), r = vec.begin(); i != vec.end(); i++){
        while(l != vec.end() && *l < *i + c) l++;
        if(l == vec.end()) break;
        while(r != vec.end() && *r <= *i + c) r++;
        ans += r - l;
    }
    cout << ans;
    return 0;
}
