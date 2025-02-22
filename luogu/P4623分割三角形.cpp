#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
int n, m, l, maxlx, maxly, tx, ty, x1, x2, x3, _y1, y2, y3, xbmin = 0xfffffff, ybmin = 0xfffffff, xbmax, ybmax, tagy[1000005], tagx[1000005], ansy[1000005], ansx[1000005];
char c1, c2;
void scan(){
    if(c1 == 'x'){
        for(int i = maxlx; i <= l; i++){
            tx += tagx[i];
            ansx[i] = tx;
        }
        maxlx = l + 1;
    }else{
        for(int i = maxly; i <= l; i++){
            ty += tagy[i];
            ansy[i] = ty;
        }
        maxly = l + 1;
    }
}
void solve(){
    cin >> n;
    while(n--){
        cin >> x1 >> _y1 >> x2 >> y2 >> x3 >> y3;
        int xmax = max(max(x1, x2), x3);
        int xmin = min(min(x1, x2), x3);
        int ymax = max(max(_y1, y2), y3);
        int ymin = min(min(_y1, y2), y3);
        xbmin = min(xmin, xbmin);
        ybmin = min(ymin, ybmin);
        xbmax = max(xmax, xbmax);
        ybmax = max(ymax, ybmax);
        tagy[ymax]--, tagx[xmax]--;
        tagy[ymin + 1]++, tagx[xmin + 1]++;
    }
    maxlx = xbmin, maxly = ybmin;
    cin >> m;
    while(m--){
        cin >> c1 >> c2 >> l;
        if(c1 == 'x'){
            if(l < xbmin || l > xbmax){
                cout << 0 << endl;
                continue;
            }else if(l >= maxlx){
                scan();
            }
            cout << ansx[l] << endl;
        }else{
            if(l < ybmin || l > ybmax){
                cout << 0 << endl;
                continue;
            }else if(l >= maxly){
                scan();
            }
            cout << ansy[l] << endl;
        }
    }
}
int main()
{
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}