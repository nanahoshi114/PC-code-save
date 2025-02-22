#include <iostream>
#include <cstring>
using namespace std;
struct number{
    int l, r;
}a[100005];
int n, k, p, m, st = 1, ma[100005];

int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n;
    
    for(int i = 2; i <= n; i++){
        cin >> k >> p;
        if(p){
            if(a[k].r > 0){
                a[a[k].r].l = i;
                a[i].r = a[k].r;
            }
            a[k].r = i;
            a[i].l = k;
        }else{
            if(a[k].l > 0){
                a[a[k].l].r = i;
                a[i].l = a[k].l;
            }else{
                st = i;
            }
            a[k].l = i;
            a[i].r = k;
        }
    }
    cin >> m;
    while(m--){
        cin >> k;
        ma[k] = 1;
    }
    while(st){
        if(!ma[st]) cout << st << ' ';
        st = a[st].r;
    }
    return 0;
}