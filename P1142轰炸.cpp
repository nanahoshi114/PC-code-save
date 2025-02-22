#include <iostream>
#include <map>
#include <set>
using namespace std;
int gcd(int x, int y){
    if(y == 0) return x;
    return gcd(y, x % y);
}
struct point{
    int x, y;
    bool operator<(point r) const {
        if(x != r.x) return x < r.x;
        return y < r.y;
    }
}p[705];
struct line{
    int a, b, c;
    explicit line(int ta, int tb, int tc){
        a = ta, b = tb, c = tc;
    }
    bool operator<(line r) const {
        if(a != r.a){
            return a < r.a;
        }else if(b != r.b){
            return b < r.b;
        }else{
            return c < r.c;
        }
    }
};
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n;
    map<line, int> mp;
    map<point, set<line>> pt;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> p[i].x >> p[i].y;
    }
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            int y1 = p[i].y, y2 = p[j].y, x1 = p[i].x, x2 = p[j].x;
            int ta = y1 - y2, tb = x2 - x1, tc = -x1 * (y1 - y2) + y1 * (x1 - x2);
            int t = gcd(gcd(ta, tb), tc);
            ta /= t, tb /= t, tc /= t;
            line next(ta, tb, tc);
            int c1 = pt[p[i]].count(next), c2 = pt[p[j]].count(next);
            if(c1 && c2) continue;
            if(!c1 && !c2) mp[next] += 2;
            else mp[next]++;
            pt[p[i]].insert(next);
            pt[p[j]].insert(next);
        }
    }
    int ans = 0;
    for(auto i : mp){
        cout << i.first.a << ' ' << i.first.b << ' ' << i.first.c << ' ' << i.second << '\n';
        ans = max(ans, i.second);
    }
    cout << ans;
    return 0;
}