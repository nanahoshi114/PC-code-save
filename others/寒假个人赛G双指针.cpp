#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(){ 
    cin.tie(0)->sync_with_stdio(0); cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    int num[4] = {0, n, m, k};
    string brl;
    cin >> brl;
    if(brl.size() == 1){
        cout << 0;
        return 0;
    }
    int orglen = brl.size();
    brl = " " + brl + brl;
    vector<int> seq;
    for(int i = 1; i + 1 <= brl.size() - 1; i += 2){
        if(brl[i] == '1' && brl[i + 1] == '0' || brl[i] == '0' && brl[i + 1] == '1') seq.push_back(2);
        else if(brl[i] == '0' && brl[i + 1] == '0') seq.push_back(1);
        else seq.push_back(3);
    }
    int l = 0, r = 0;
    int ans = 0;

    while(r < seq.size()){
        while(l < seq.size() && l == r && !num[seq[l]]){
            l++, r++;
        }
        while(r < seq.size() && num[seq[r]]){
            num[seq[r]]--;
            r++;
            if(r - l <= orglen / 2) ans = max(ans, (r - l) * 2);
        }
        while(l < r && (r == seq.size() || !num[seq[r]])){
            num[seq[l]]++; l++;
        }
    }

    seq.clear();
    for(int i = 2; i + 1 <= brl.size() - 1; i += 2){
        if(brl[i] == '1' && brl[i + 1] == '0' || brl[i] == '0' && brl[i + 1] == '1') seq.push_back(2);
        else if(brl[i] == '0' && brl[i + 1] == '0') seq.push_back(1);
        else seq.push_back(3);        
    }
    l = r = 0;
    while(r < seq.size()){
        while(l < seq.size() && l == r && !num[seq[l]]){
            l++, r++;
        }
        while(r < seq.size() && num[seq[r]]){
            num[seq[r]]--;
            r++;
            if(r - l <= orglen / 2) ans = max(ans, (r - l) * 2);
        }
        while(l < r && (r == seq.size() || !num[seq[r]])){
            num[seq[l]]++; l++;
        }
    }
    cout << ans;
    return 0;
}