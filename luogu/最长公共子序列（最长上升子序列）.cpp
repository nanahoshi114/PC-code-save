#include <iostream>
#include <algorithm>
using namespace std;
int p1[100005], p2[100005], n, len = 1, f[100005]/*f[i] 长度为i的最长上升子序列最小结尾数值*/, x;
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> x;
        p1[x] = i;
    }
    for(int i = 1; i <= n; i++){
        cin >> x;
        p2[p1[x]] = i;
    }
    f[len] = p2[1];
    for(int i = 2; i <= n; i++){
        if(f[len] <= p2[i]) f[++len] = p2[i];
        else{
            *upper_bound(f + 1, f + len, p2[i]) = p2[i];
        }
    }
    cout << len;
	return 0;
}