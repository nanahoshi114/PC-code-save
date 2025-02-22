#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;
struct word{
    string s;
    vector<pair<int, int>/*index, sizetominus*/> next_ind;
    int flag;
}wd[25];
int find_after(string fr, string ne){
    string s1 = "", s2 = "";
    for(auto i = fr.end() - 1, j = ne.begin(); i != fr.begin() && j != ne.end() - 1; i--, j++){
        s1.insert(s1.begin(), *i);
        s2.push_back(*j);
        if(s1 == s2) {
            return s1.size();
        }
    }
    return -1;
}
int ans, n;
void dfs(word* now, int length){
    bool flag = 0;
    for(auto i : now->next_ind){
        word* next = &wd[i.first];
        if(next->flag >= 2) continue;
        ++next->flag;
        dfs(next, length + next->s.size() - i.second);
        --next->flag;
        flag = 1;
    }
    if(!flag){
        ans = max(ans, length);
    }
}
char c;
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> wd[i].s;
    }
    cin >> c;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int temp = 0;
            if((temp = find_after(wd[i].s, wd[j].s)) != -1){
                wd[i].next_ind.push_back(make_pair(j, temp));
            }
        }
    }
    for(int i = 1; i <= n; i++){
        if(wd[i].s[0] == c){
            ++wd[i].flag;
            dfs(&wd[i], wd[i].s.size());
            --wd[i].flag;
        }
    }
    cout << ans;
    return 0;
}   