#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstring>
using namespace std;
using ll = long long;
constexpr ll mod = 998244353;
void minusStr(string &s){
    int last = 0;
    for(int i = 0; i < s.size(); i++){
        s[i] -= last;
        last = 0;
        if(i == 0) s[i] -= 1;
        if(s[i] >= '0') break;
        else{
            s[i] = '9';
            last++;
        }
    }
    while(s.back() == '0' && s.size() > 1) s.pop_back();
}
ll dp[105][1005][105][2];
ll dfs(const string &s, int pos, bool flag, bool isPrefix0, int num, int gcdans){
    if(pos == -1){
        return gcdans > 1 ? 1ll : 0ll;
    }
    if(!flag && ~dp[pos][gcdans][num - (num / 100) * 100][isPrefix0]) return dp[pos][gcdans][num - (num / 100) * 100][isPrefix0];
    ll res = 0;
    char up = flag ? s[pos] : '9';
    for(char i = '0'; i <= up; i++){
        int nextNum = (num - (num / 100) * 100) * 10 + i - '0';
        res = (res + dfs(s, pos - 1, flag && i == s[pos], isPrefix0 && nextNum < 100, nextNum, !(isPrefix0 && nextNum < 100) ? gcd(gcdans, nextNum) : 0)) % mod;
    }
    if(!flag) dp[pos][gcdans][num - (num / 100) * 100][isPrefix0] = res;
    return res;
}
void slv(){
    string ls, rs;
    cin >> ls >> rs;
    reverse(ls.begin(), ls.end());
    reverse(rs.begin(), rs.end());
    minusStr(ls);
    cout << (dfs(rs, rs.size() - 1, 1, 1, 0, 0) - dfs(ls, ls.size() - 1, 1, 1, 0, 0) + mod) % mod << '\n'; 
}
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    memset(dp, -1, sizeof(dp));
    int t;
    cin >> t;
    while(t--) slv();
    return 0;
}