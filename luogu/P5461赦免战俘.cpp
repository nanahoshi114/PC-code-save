#include <iostream>
using namespace std;
int a[2000][2000], n, l;
int pow_(int x, int y){
    int t = x;
    y--;
    while(y--){
        x *= t;
    }
    return x;
}
void func(int k, int sx, int sy){
    for(int i = sx; i < sx + k / 2; i++){
        for(int j = sy; j < sy + k / 2; j++){
            a[i][j] = 1;
        }
    }
    if(k == 2) return;
    func(k / 2, sx, sy + k / 2);
    func(k / 2, sx + k / 2, sy);
    func(k / 2, sx + k / 2, sy + k / 2);
}
int main(){
    cin >> n;
    l = pow_(2, n);
    func(l, 1, 1);
    for(int i = 1; i <= l; i++){
        for(int j = 1; j <= l; j++){
            cout << !(a[i][j]) << ' ';
        }
        cout << endl;
    }
    return 0;
}