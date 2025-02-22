#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
double a, b, c, d, sol[3];
int t = 0;
double tri_func(double x){
    return a * x*x*x + b * x*x + c * x + d;
}
double bi_s(double left, double right){ //Ç°Ìב: f(left)*f(right)<0
    double mid = 0;
    while(right - left >= 0.001){
        mid = (left + right) / 2;
        if(tri_func(mid) * tri_func(right) <=0){
            left = mid;
        }else{
            right = mid;
        }
    }
    return mid;
}
int main(){
    cin >> a >> b >> c >> d;
    for(double i = -100, left = 0, right = 0; i <= 100 && t < 2; i++){
        left = tri_func(i), right = tri_func(i + 1);
        if(left * right <= 0){
            if(left == 0){
                sol[t++] = i;
            }else if(right == 0){
                continue;
            }else{
                sol[t++] = bi_s(i, i + 1);
            }
        }
    }
    sol[2] = -b/a - sol[0] - sol[1];
    cout << fixed << setprecision(2) << sol[0] << ' ' << sol[1] << ' ' << sol[2];
    return 0;
}