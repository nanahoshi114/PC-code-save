#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
using ll = long long;
struct oper{
    char sw; //'c' or 'v'
    int ind1, ind2; //ָ��ĵ�һ�����֣�ָ��ĵڶ�������
};
struct variable{
    int qi, ind; //�ڶ����е�λ�ã��Ǽ��Ŷ���
    bool flag; //�Ƿ񱻲�����
};
struct channel{
    vector<int> que; //channel�Ķ���
    int ind; //����front���±꣨==���ڣ�
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
    while(m--){ //��ָ��洢��vec
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
    for(auto i : vec){ //����ָ��
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