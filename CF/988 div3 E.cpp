#include <iostream>
#include <string>
using namespace std;
void slv(){
    string s;
    int n, t, pre;
    bool tag = 0;
    cin >> n;
    for(int i = 2; i <= n; i++, pre = t){
        cout << "? 1 " << i << endl;
        cin >> t;
        if(tag){
            if(t != pre){
                s.push_back('1');
            }else{
                s.push_back('0');
            }
        }else{
            if(t){
                s = string(i - 1 - t, '1') + string(t, '0');
                s.push_back('1');
                tag = 1;
            }
        }
    }
    if(!tag){
        cout << "! IMPOSSIBLE" << endl;
    }else{
        cout << "! " << s << endl;
    }
}
int main(){
	//ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        slv();
    }
	return 0;
}