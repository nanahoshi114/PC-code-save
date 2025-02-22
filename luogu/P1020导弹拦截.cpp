#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 5;
int n, f1[MAXN], f2[MAXN], ans2 = 1, ans1 = 1, a[MAXN];
bool cmp(int a, int b){
    return a > b;
}
void find_lis(){
    f1[ans1] = f2[ans2] = a[1];
    for(int i = 2; i <= n; i++){
        if(f1[ans1] >= a[i]) f1[++ans1] = a[i]; //求最长不升子序列
        else{
            *upper_bound(f1 + 1, f1 + 1 + ans1, a[i], cmp) = a[i]; 
        }
        if(f2[ans2] < a[i]) f2[++ans2] = a[i]; //求最长上升子序列
        else{
            *lower_bound(f2 + 1, f2 + 1 + ans2, a[i]) = a[i];
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    while(cin >> a[++n]);
    n--;
    find_lis();
    cout << ans1 << '\n' << ans2;
	return 0;
}