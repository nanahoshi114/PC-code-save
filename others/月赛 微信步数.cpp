#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;
using ll = long long;
const int MAXN = 100005;
ll n, m, k;
ll sum, bic[MAXN];
pair<ll, ll> wat[MAXN];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n >> m >> k;
    for(int i = 1; i <= m; i++){
        cin >> wat[i].first >> wat[i].second;
        sum += wat[i].second - wat[i].first + 1;
    }
    for(int i = 1; i <= k; i++) cin >> bic[i];
    sort(wat + 1, wat + 1 + m);
    sort(bic + 1, bic + 1 + k);
    int it = 1;
    for(int i = 1; i <= m; i++){
        if(it < k && bic[it + 1] < wat[i].first){
            while(it < k && bic[it + 1] <= wat[i].first) it++; //���ˮ�����϶�ˮ��֮���Ƿ��г�������У����µ�����ĳ������ϳ���ˮ�ݵ�·��
            sum += wat[i].first - bic[it];
        }else{
            sum += wat[i].first - ((i == 1) ? bic[it] : (wat[i - 1].second + 1)); //���û�У�·�̼����϶�ˮ�ݵ����ˮ�ݵľ���
        }
    }
    cout << n - sum;
    return 0;
}