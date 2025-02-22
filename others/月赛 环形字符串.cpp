#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;
int n, ans;
char last, now;
vector<pair<char, int>> vec;
int main(){
    cin >> n;
    cin >> now;
    vec.push_back(make_pair(now, 1));
    for(int i = 2; i <= n; i++){
        cin >> now;
        while(now){
            if(!vec.empty() && now == vec.back().first){
                vec[vec.size() - 1].second++;
                if(vec.back().second == 2){
                    vec[vec.size() - 1].second = 0;
                    ans += 2;
                }
                now = 0;
            }else{
                if(!vec.empty() && vec.back().second == 0){
                    vec.pop_back();
                }else{
                    vec.push_back(make_pair(now, 1));
                    now = 0;
                }
            }   
        }
    }
    if(!vec.empty() && vec.back().second == 0) vec.pop_back();
    while(vec.size() >= 2 && vec.front().first == vec.back().first){
        vec.erase(vec.begin());
        vec.pop_back(); 
        ans += 2;
    }
    cout << ans;
    return 0;
}