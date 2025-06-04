#include <iostream>
#include <vector>
#include <random>
#include <array>
#include <optional>
using i64 = long long;

class Hash_RangeQuery {
    std::random_device rd;
    std::mt19937 generator;
    std::uniform_int_distribution<i64> rnd;
    i64 M1, M2;
    i64 base = 131;
    std::vector<std::array<i64, 2>> prem, preb;
public:
    explicit Hash_RangeQuery(const std::string& s) : generator(rd()), rnd(1e8, 1e9) {
        M1 = rnd(generator);
        M2 = rnd(generator);
        prem.assign(s.size() + 1, std::array{0ll, 0ll});
        preb.assign(s.size() + 1, std::array{0ll, 0ll});
        for(int i = 1; i <= s.size(); i++){
            prem[i][0] = (prem[i - 1][0] * base + s[i - 1]) % M1;
            prem[i][1] = (prem[i - 1][1] * base + s[i - 1]) % M2;
        }
        preb[0][0] = preb[0][1] = 1;
        for(int i = 1; i <= s.size(); i++){
            preb[i][0] = preb[i - 1][0] * base % M1;
            preb[i][1] = preb[i - 1][1] * base % M2;
        }
    }
    auto query(int l, int r) const {
        return std::pair((prem[r + 1][0] - prem[l][0] * preb[r - l + 1][0] % M1 + M1) % M1, (prem[r + 1][1] - prem[l][1] * preb[r - l + 1][1] % M2 + M2) % M2);
    }
    bool check(int l1, int r1, int l2, int r2) const {
        return query(l1, r1) == query(l2, r2);
    }
};
auto manacher(const std::string &s){
    std::vector<int> d1(s.size() + 5, 0);
    for(int i = 0, l = 0, r = -1; i < s.size(); i++){
        if(i <= r) d1[i] = std::min(d1[l + r - i], r - i + 1);
        while(0 <= i - d1[i] && i + d1[i] < s.size() && s[i - d1[i]] == s[i + d1[i]]){
            d1[i]++;
        }
        if(i + d1[i] - 1 > r){
            l = i - d1[i] + 1;
            r = i + d1[i] - 1;
        }
    }
    return d1;
}
void slv() {
    std::string s;
    std::cin >> s;
    int n = s.size();
    s = " " + s;
    int l = 1, r = 1, dx = 1;
    i64 ans = 0;
    auto posmove = [&]() {
        if (r != 1) {
            if (l == 1) {
                dx = 1;
            } 
            if (l == r) {
                dx = -1;
            }
            l += dx;
        }
    };
    Hash_RangeQuery hash(s);
    auto manacher_ans = manacher(s);
    auto check = [&](int nowpos, int nowi) ->std::optional<std::pair<int, int>> {
        if (nowpos == 1) return std::nullopt;
        int nowr = nowpos + nowpos - 2;
        if (nowi < nowr) {
            if (manacher_ans[nowpos] < nowi - nowpos + 1) {
                return std::nullopt;
            } 
            return std::pair(nowpos - (nowi - nowpos), -1);
        }
        if (manacher_ans[nowpos] < nowr - nowpos + 1) {
            return std::nullopt;
        }
        int l, r;
        for (l = nowr + 1, r = 2 * nowr; r <= nowi; l += nowr, r += nowr) {
            if (!hash.check(1, nowr, l, r)) {
                return std::nullopt;
            }
        }
        if (l <= nowi) {
            if (hash.check(1, nowi - l + 1, l, nowi)) {
                if (nowi - l - 1 <= nowpos) {
                    return std::pair(nowi - l - 1, 1);
                } else {
                    return std::pair(nowi - nowpos, -1);
                }
            } else {
                return std::nullopt;
            }
        }
        return std::pair(nowr, -1);
    };
    for (int i = 1; i <= n; ++i) {
        posmove();
        if (s[i] != s[l]) {
            for (int j = r; j <= i; ++j) {
                if (j == i) {
                    r = l = j;
                } else {
                    auto res = check(j, i);
                    if (res) {
                        r = j;
                        l = res->first;
                        dx = res->second;
                        break;
                    }
                }
            }
        }
        ans ^= (i64(i) * i64(r));
    }
    std::cout << ans << '\n';
    
}
int main() {
    //std::freopen("data.txt", "r", stdin);
    //std::freopen("cs1.txt", "w", stdout);
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    std::cin >> t;
    while(t--) slv();
    return 0;
}