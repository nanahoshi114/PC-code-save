#include <iostream>
#include <algorithm>
using namespace std;
int amax[10005], rmax[10005], n, a[10005], sum;
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        amax[i] = max(amax[i - 1], a[i]);
    }
    for(int i = n; i >= 1; i--){
        rmax[i] = max(rmax[i + 1], a[i]);
    }
    for(int i = 1; i <= n; i++){
        if(min(amax[i], rmax[i])) sum += min(amax[i], rmax[i]) - a[i];
    }
    cout << sum;
	return 0;
}