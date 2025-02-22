#include <iostream>
#include <vector>
using namespace std;
int n;
bool query(int x, int y){
    bool t;
    cout << "? " << x << ' ' << y << endl;
    cin >> t;
    return t;
}
void slv(){
    cin >> n;
    vector<int> ans;
    int minind = n - 2;
    for(int i = n - 1; i >= 1; i--){
        if(minind == 0) ans.push_back(0);
        while(minind >= 1){
            if(!query(minind, i)){
                ans.push_back(minind);
                minind--;
                break;
            }
            minind--;
        }
    }
    cout << '!';
    for(auto i = ans.rbegin(); i != ans.rend(); i++){
        cout << ' ' << *i;
    }
    cout << endl;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        slv();
    }
    return 0;
}