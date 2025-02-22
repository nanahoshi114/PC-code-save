#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
void slv(){
    int n, m;
    cin >> n >> m;
    vector<int> tag1(n + 1, 0), tag2(n + 1, 0);
    while(m--){
        int opt, x;
        cin >> opt >> x;
        if(opt == 1) tag1[x]++;
        else tag2[x]++;
    }
    vector<int> pn(n + 1, 0);
    for(int i = 1, t = 0; i <= n; i++){
        pn[i] = (pn[i - 1] + tag2[i] + t) % mod;
        t += tag2[i] * 2;
    }
    for(int i = 1, t = 0; i <= n; i++){
        t += tag1[i];
        pn[i] = (pn[i] + pn[i - 1] + t) % mod;
        cout << pn[i] << ' ';
    }
    cout << '\n';
}
int main(){
    int t;
    cin >> t;
    while(t--) slv();
    return 0;   
}