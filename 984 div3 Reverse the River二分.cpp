#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int M = 1e5 + 5;
int n, k, q, m, l, r;
char c;
vector<vector<int>> arr;
int slv(){
	int ansl = 1, ansr = n;
	cin >> m;
	while(m--){
		cin >> l >> c >> r;
		if(c == '<'){
			int it = upper_bound(arr[l].rbegin(), arr[l].rend(), r, [](int a, int b){return a > b;}) - arr[l].rbegin();
			ansr = min(ansr, n - it);
		}else{
			int it = upper_bound(arr[l].begin(), arr[l].end(), r) - arr[l].begin() + 1;
			ansl = max(ansl, it);
		}
	}
	//cout << ansl << ' ' << ansr << '\n';
	return (ansr >= ansl) ? ansl : -1;
	
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> k >> q;
	arr = vector<vector<int>>(k + 1, vector<int>());
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= k; j++){
			int t;
			cin >> t;
			arr[j].push_back((arr[j].empty() ? 0 : (arr[j].back())) | t);
		}
	}
	while(q--){
		cout << slv() << '\n';
	}
	return 0;
}	