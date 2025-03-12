#include <cstdio>
#include <cctype>
#include <print>
#include <vector>
using namespace std;
struct istream{
	template<typename T>
	istream& operator>>(T &x){
		x = 0;
		int fl = 1;
		int ch = getchar();
		for(; !isdigit(ch); ch = getchar()){
			if(ch == '-') fl = -1;
		}
		for(; isdigit(ch); ch = getchar()){
			x = x * 10 + ch - '0';
		}
		return *this;
	}	
}cin;
int main(){
	//freopen("testin.txt", "r", stdin);
	int n, m, h, w;
	cin >> n >> m >> h >> w;
	vector<vector<int>> a(n + 1, vector<int>(m + 1));
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> a[i][j];
		}
	}
	auto check = [&](int x){
		vector<vector<int>> psum(n + 1, vector<int>(m + 1));
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				psum[i][j] = psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1] + (a[i][j] > x);
			}
		}
		for(int i = h; i <= n; i++){
			for(int j = w; j <= m; j++){
				int cnt = psum[i][j] - psum[i - h][j] - psum[i][j - w] + psum[i - h][j - w];
				if(cnt <= h * w / 2){
					return true;
				}
			}
		}
		return false;
	};
	int l = 1, r = n * m, mid;
	while(l < r){
		mid = (l + r) >> 1;
		if(check(mid)){
			r = mid;
		}else{
			l = mid + 1;
		}
	}
	println("{}", l);
	return 0;
}