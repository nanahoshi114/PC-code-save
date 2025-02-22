#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
using ll = long long;
struct oper{
    char sw; //'c' or 'v'
    int ind1, ind2; //指令的第一个数字，指令的第二个数字
};
struct variable{
    int qi, ind; //在队列中的位置，是几号队列
    bool flag; //是否被操作过
};
struct channel{
    vector<int> que; //channel的队列
    int ind; //队列front的下标（==周期）
};
ll n, m, q;
void solve();
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
void solve(){
    cin >> n >> m >> q;
    vector<variable> var(n + 1, {0, 0, 0});
    vector<oper> vec;
    map<int, channel> chan;
    while(m--){ //将指令存储进vec
        string s;
        cin >> s;
        oper t = {};
        if(s[0] == 'c'){ 
            t.sw = 'c';
            int i = 0, fl = 1;
            for(i = 4; s[i] != '<'; i++){
                t.ind1 = t.ind1 * 10 + s[i] - '0';
            }
            for(i += 2; i < s.size(); i++){
                if(s[i] == '-'){
                    fl = -1;
                }else{
                    t.ind2 = t.ind2 * 10 + s[i] - '0';
                }
            }
            t.ind2 *= fl;
        }else{
            t.sw = 'v';
            int i = 0;
            for(i = 3; s[i] != '<'; i++){
                t.ind1 = t.ind1 * 10 + s[i] - '0';
            }
            for(; i < s.size(); i++){
                if('0' <= s[i] && s[i] <= '9'){
                    t.ind2 = t.ind2 * 10 + s[i] - '0';
                }
            }
        }
        vec.push_back(t);
        //cout << t.sw << ' ' << t.ind1 << ' ' << t.ind2 << endl;
    }
    for(auto i : vec){ //遍历指令
        if(i.sw == 'c'){
            chan[i.ind1].que.push_back(i.ind2);
        }else{
            if(chan[i.ind2].ind >= chan[i.ind2].que.size()){
                cout << "panic" << endl;
                return ;
            }
            var[i.ind1].flag = 1;
            var[i.ind1].qi = chan[i.ind2].ind;
            var[i.ind1].ind = i.ind2;
            chan[i.ind2].ind++;
        }
    }
    for(int i = 1; i <= n; i++){
        if(!var[i].flag) cout << 0 << ' ';
        else cout << chan[var[i].ind].que[((ll)var[i].qi + ((ll)chan[var[i].ind].ind * (q - 1))) % chan[var[i].ind].que.size()] << ' ';
    }
    cout << endl;
}