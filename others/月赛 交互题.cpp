#include <iostream>
#include <map>
#include <vector>
using namespace std;
int n;
map<int, int> ma; // <type, time>
int tag;
vector<int> vec;
int main(){
    cin >> n;
    cout << '?' << endl;
    for(int i = 1; i <= n; i++){
        int t;
        cin >> t;
        ma[t]++;
    }
    while(1){
        if(tag == 0){
            cout << '?' << endl;
            vec.clear();
            map<int, int> tmap;
            for(int j = 1; j <= n; j++){
                int t;
                cin >> t;
                vec.push_back(t);
                tmap[t]++;
                if(ma[t] == 0 && t != 0){
                    cout << "! " << j << endl;
                    return 0;
                }
            }
            for(auto it = ma.begin(); it != ma.end(); it++){
                if(it->first == 0) continue;
                if(tmap[it->first] > it->second){
                    tag = it->first;
                }
            }
            ma = tmap;
        }else{
            for(auto it = vec.begin(); it != vec.end(); it++){
                if(*it != tag){
                    cout << "# " << it - vec.begin() + 1 << endl;
                    ma[*it] = 0;
                }
            }
            tag = 0;
        } 
    }
    return 0;
}