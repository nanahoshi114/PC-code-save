#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int n;
string s[2000];
void add_space(string &ts, int i, int num){
    while(num--) ts.insert((i == 1) ? ts.begin() : ts.end(), ' '); 
}
void dfs(int lv, int ind){ // level, last index (ind = 2 ^ (lv - 1))
    if(lv > n) return;
    for(int i = 1, j = ind + 1; i <= ind; i++, j++){
        s[j] = s[i];
    }
    for(int i = ind + 1, j = ind - 1; i <= ind * 2; i++, j--){
        add_space(s[i], 2, j);
        for(auto k = s[i - ind].begin(); k != s[i - ind].end(); k++) s[i].push_back(*k);
    }
    for(int i = 1; i <= ind; i++){
        add_space(s[i], 1, ind);
    }
    dfs(lv + 1, ind * 2);
}
int main(){
    cin >> n;
    s[1] = " /\\";
    s[2] = "/__\\";
    dfs(2, 2);
    for(int i = 1; i <= pow(2, n); i++){
        cout << s[i] << endl;
    }
    return 0;
}