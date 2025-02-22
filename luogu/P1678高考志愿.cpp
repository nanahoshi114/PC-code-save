#include <iostream>
#include <algorithm>
using namespace std;
int m, n, a[100200], tmp, *tmp_t;
long long total;
int main(){
    cin >> m >> n;
    for(int i = 0; i < m; i++){
        cin >> a[i];
    }
    sort(a, a + m);
    for(int i = 0; i < n; i++){
        cin >> tmp;
        tmp_t = lower_bound(a, a + m, tmp);
        if(tmp_t - a == m && tmp >= *(tmp_t - 1)) total += tmp - *(tmp_t - 1); 
        else if(tmp_t - a == 0) total += abs(*tmp_t - tmp);
        else total += min(abs(tmp - *(tmp_t - 1)), abs(*tmp_t - tmp));
    }
    cout << total;
    return 0;
}