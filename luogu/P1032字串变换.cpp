#include <iostream>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
string a, b;
string r1[1000],r2[1000], tmp_s;
int t, tmp, minc = 11, k = 2;
map<string, int> st; //<key, step>
void search(string s, int count){
    if(count > k) return ;
    if(s == b){
        minc = min(minc, count);
        return ;
    }
    if(st.find(s) != st.end()){
        if(st[s] <= count) return ;
    }
    st[s] = count;
    for(int i = 0; i < t; i++){
        tmp = s.find(r1[i]);
        while(tmp >= 0 && tmp < s.length()){
            tmp_s = s;
            search(tmp_s.replace(tmp, r1[i].length(), r2[i]), count + 1);
            tmp = s.find(r1[i], tmp + 1);
        }
    }
    return ;
}
int main(){
    cin >> a >> b;
    while(cin >> r1[t] >> r2[t]) t++;
    while(minc == 11){
        search(a, 0);
        st.clear();
        k++;
        if(k == 11) break;
    }
    search(a, 0);
    if(minc == 11){
        cout << "NO ANSWER!";
    }else{
        cout << minc;
    }
    return 0;
}