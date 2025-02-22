#include <iostream>
using namespace std;
bool flag[25];
int a[25], mina, ans;
void dfs(int n, int l, int r, int step){
    if(step >= n){
        mina = min(mina, max(l, r));
        return;
    }
    dfs(n, l + a[step + 1], r, step + 1);
    dfs(n, l, r + a[step + 1], step + 1);
}
void read(int n){
    mina = 1e9;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    dfs(n, a[1], 0, 1);
    ans += mina;
}
int main(){
    int s1, s2, s3, s4;
    cin >> s1 >> s2 >> s3 >> s4;
    read(s1);read(s2);read(s3);read(s4);
    cout << ans;
	return 0;
}