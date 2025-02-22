#include <iostream>
#include <cmath>
using namespace std;
const int M = 2e5 + 5;
struct Node{
    int step, to, val;
}arr[M];
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n, m;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> arr[i].val;
    }
    int blsize = sqrt(n);
    auto rebuildBlock = [&](int l, int r){
        for(int i = r; i >= l; i--){
            if(i + arr[i].val > r){
                arr[i].step = 1;
                arr[i].to = i + arr[i].val;
            }else{
                arr[i].step = arr[i + arr[i].val].step + 1;
                arr[i].to = arr[i + arr[i].val].to;
            }
        }
    };
    for(int i = 1; i <= blsize; i++){
        rebuildBlock((i - 1) * blsize + 1, i * blsize);
    }
    rebuildBlock(blsize * blsize + 1, n);
    auto query = [&](int x){
        int cnt = 0;
        for(int ind = x; ind <= n; ind = arr[ind].to){
            cnt += arr[ind].step;
        }
        return cnt;
    };
    auto update = [&](int ind, int val){
        int blockn = (ind / blsize) + (ind % blsize != 0);
        arr[ind].val = val;
        rebuildBlock((blockn - 1) * blsize + 1, blsize * blockn);
    };
    cin >> m;
    while(m--){
        int opt, a, b;
        cin >> opt >> a;
        a++;
        if(opt == 1){
            cout << query(a) << '\n';
        }else{
            cin >> b;
            update(a, b);
        }
    }
    return 0;
}