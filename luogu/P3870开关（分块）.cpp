#include <iostream>
#include <algorithm>
#include <bitset>
#include <cmath>
using namespace std;
const int M = 1e5 + 5;
int totalSum[1005], tag[1005];
int main(){
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    bitset<M> state;
    int blsize = sqrt(n);
    auto updateInBlock = [&](int x){
        if(tag[x] % 2){
            for(int i = (x - 1) * blsize + 1; i <= x * blsize; i++){
                state[i] = !state[i];
            }
        }
        tag[x] = 0;
    };
    auto update = [&](int l, int r){
        int blockl = l / blsize + (l % blsize != 0), blockr = r / blsize + (r % blsize != 0);
        updateInBlock(blockl); updateInBlock(blockr);
        if(blockl == blockr){
            for(int i = l; i <= r; i++){
                if(state[i]) totalSum[blockl]--;
                else totalSum[blockl]++;
                state[i] = !state[i];
            }
        }else{
            for(int i = l; i <= blockl * blsize; i++){
                if(state[i]) totalSum[blockl]--;
                else totalSum[blockl]++;
                state[i] = !state[i];
            }
            for(int i = blockl + 1; i < blockr; i++){
                totalSum[i] = blsize - totalSum[i];
                tag[i]++;
            }
            for(int i = (blockr - 1) * blsize + 1; i <= r; i++){
                if(state[i]) totalSum[blockr]--;
                else totalSum[blockr]++;
                state[i] = !state[i];                
            }
        }
    };
    auto query = [&](int l, int r){
        int blockl = l / blsize + (l % blsize != 0), blockr = r / blsize + (r % blsize != 0);
        updateInBlock(blockl); updateInBlock(blockr);
        int cnt = 0;
        if(blockl == blockr){
            for(int i = l; i <= r; i++) cnt += state[i];
            return cnt;
        }
        for(int i = l; i <= blockl * blsize; i++) cnt += state[i];
        for(int i = blockl + 1; i < blockr; i++) cnt += totalSum[i];
        for(int i = (blockr - 1) * blsize + 1; i <= r; i++) cnt += state[i];
        return cnt;
    };
    while(m--){
        int opt, a, b;
        cin >> opt >> a >> b;
        if(opt == 0){
            update(a, b);
        }else{
            cout << query(a, b) << '\n';
        }
    }
    return 0;
}