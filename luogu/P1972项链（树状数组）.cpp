#include <cstdio>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;
using ll = long long;
const int M = 1e6 + 5;
struct Query{
    int l, r, ind, ans;
};
void read(int &x){
    char ch;
    x = 0;
    for(ch = getchar(); !isdigit(ch); ch = getchar());
    for(; isdigit(ch); ch = getchar()){
        x = x * 10 + ch - '0';
    }
}
class BIT{
    vector<int> tree;
    int size;
    int lowbit(int x){
        return x & -x;
    }
    int query(int x){
        int sum = 0;
        while(x){
            sum += tree[x];
            x -= lowbit(x);
        }
        return sum;
    }
public:
    BIT(int _size){
        size = _size; tree.resize(size + 1, 0);
    }
    void update(int x, int ind){
        for(int i = ind; i <= size; i += lowbit(i)){
            tree[i] += x;
        }
    }
    int query(int l, int r){
        return query(r) - query(l - 1);
    }
};
int main(){
    //cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n, q, maxsize = 0;
    read(n);
    vector<int> org(n + 1);
    for(int i = 1; i <= n; i++){
        read(org[i]);
        maxsize = max(maxsize, org[i]);
    }
    vector<int> mp(maxsize + 1, 0);
    read(q);
    vector<Query> query;
    for(int i = 1; i <= q; i++){
        Query now = {};
        read(now.l); read(now.r);
        now.ind = i;
        query.push_back(now);
    }
    sort(query.begin(), query.end(), [](Query ql, Query qr){
        return ql.r < qr.r;
    });
    BIT bit(n);
    int i = 1;
    for(auto &now : query){
        for(; i <= now.r; i++){
            if(mp[org[i]]){
                bit.update(-1, mp[org[i]]);
            }
            bit.update(1, i);
            mp[org[i]] = i;
        }
        now.ans = bit.query(now.l, now.r);
    }
    sort(query.begin(), query.end(), [](Query ql, Query qr){
        return ql.ind < qr.ind;
    });
    for(auto &now : query){
        printf("%d\n", now.ans);
    }
    return 0;
}