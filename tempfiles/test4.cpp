#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cstring>
#include <cmath>
#include <unordered_set>
#include <bitset>
#include <cstdio>
#define int long long
using namespace std;
using ll = long long;
struct specialNum{
    int A, len;
    ll realnum;
    int num[20];
    specialNum(int x, int _A) : A(_A), realnum(x){
        len = 0;
        memset(num, 0, sizeof(num));
        while(x){
            num[len++] = x % A;
            x /= A;
        }
    }
    specialNum(){
        A = len = realnum = 0;
        memset(num, 0, sizeof(num));
    }
    void reset(int x, int _A){
        A = _A, realnum = x;
        len = 0;
        memset(num, 0, sizeof(num));
        while(x){
            num[len++] = x % A;
            x /= A;
        }        
    }
    specialNum operator&(const specialNum & r){
        specialNum res;
        res.A = A;
        res.realnum = 0;
        res.len = max(len, r.len);
        for(int i = 0, p = 1; i < res.len; i++, p *= A){
            res.num[i] = min(num[i], r.num[i]);
            res.realnum += res.num[i] * p;
        }
        return res;
    }
    specialNum operator|(const specialNum & r){
        specialNum res;
        res.A = A;
        res.realnum = 0;
        res.len = max(len, r.len);
        for(int i = 0, p = 1; i < res.len; i++, p *= A){
            res.num[i] = max(num[i], r.num[i]);
            res.realnum += res.num[i] * p;
        }
        return res;
    }
    specialNum operator^(const specialNum & r){
        specialNum res;
        res.A = A;
        res.realnum = 0;
        res.len = max(len, r.len);
        for(int i = 0, p = 1; i < res.len; i++, p *= A){
            res.num[i] = (num[i] + r.num[i]) % A;
            res.realnum += res.num[i] * p;
        }
        return res;
    }
};
specialNum a[1005];
int n, A, x;
bitset<100000> vis[1005];
unordered_set<ll> st;
void dfs(specialNum now, int ind){
    if(vis[ind][now.realnum]) return ;
    vis[ind][now.realnum] = 1;
    if(ind == n + 1){
        st.insert(now.realnum);
        return ;
    }
    dfs(now & a[ind], ind + 1);
    dfs(now | a[ind], ind + 1);
    dfs(now ^ a[ind], ind + 1);
}
void slv(){
    cin >> n >> A >> x;
    for(int i = 1; i <= n; i++){
        vis[i] = 0;
    }
    specialNum spx(x, A);
    for(int i = 1, t; i <= n; i++){
        cin >> t;
        a[i].reset(t, A);
    }
    st.clear();
    dfs(spx, 1);
    ll ans = 0;
    for(auto &i : st){
        ans += i;
    }
    cout << ans << '\n';
}
signed main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    //freopen("data.txt", "r", stdin);
    //freopen("cs1.txt", "w", stdout);
    int t;
    cin >> t;
    while(t--) slv();
    return 0;
}