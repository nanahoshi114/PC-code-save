#include <iostream>
#include <vector>
using namespace std;
struct res{
    int maxa = 0;
    vector<int> step;

};
int n, ans, a[40];
res flag[40][40];
vector<int> ansl;
res dfs(int l, int r){
    if(l > r){
        return (res){1};
    }
    if(l == r){ 
        vector<int> t;
        t.push_back(l);
        return (res){a[l], t};
    }
    if(flag[l][r].maxa) return flag[l][r];
    int anst = 0;
    int it = 0;
    vector<int> ans1, ans2;
    for(int i = l; i <= r; i++){
        res t1 = dfs(l, i - 1);
        res t2 = dfs(i + 1, r);
        int t = t1.maxa * t2.maxa + a[i];
        if(t > anst){
            anst = t;
            it = i;
            ans1 = t1.step;
            ans2 = t2.step;
        }
    }
    vector<int> ansv;
    ansv.push_back(it);
    for(auto i : ans1){
        ansv.push_back(i);
    }
    for(auto i : ans2){
        ansv.push_back(i);
    }
    flag[l][r] = (res){anst, ansv};
    return flag[l][r];
}
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }
    res a = dfs(1, n);
    ansl = a.step;
    cout << a.maxa << endl;
    for(auto i : ansl){
        cout << i << ' ';
    }
    return 0;
}