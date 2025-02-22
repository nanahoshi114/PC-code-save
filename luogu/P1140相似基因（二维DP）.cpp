#include <cstdio>
#include <algorithm>
using namespace std;
using ll = long long;
ll table[100][100];
ll dp[105][105], n1, n2;
char a[105] = " ", b[105] = " ";
int main(){ 
    table['A']['T'] = table['T']['A'] = table['A']['C'] = table['C']['A'] = table['T'][0] = table[0]['T'] = -1;
    table['A']['A'] = table['C']['C'] = table['G']['G'] = table['T']['T'] = 5;
    table['A']['G'] = table['G']['A'] = table[0]['G'] = table['G'][0] = table['C']['T'] = table['T']['C'] = table['G']['T'] = table['T']['G'] = -2;
    table['C']['G'] = table['G']['C'] = table['A'][0] = table[0]['A'] = -3;
    table['C'][0] = table[0]['C'] = -4;
    scanf("%lld%s", &n1, a + 1);
    scanf("%lld%s", &n2, b + 1);
    dp[1][1] = table[a[1]][b[1]];
    for(int i = 2, maxt = table[a[1]][b[1]], ch = table[a[1]][0]; i <= n1; i++){
        if(dp[i - 1][1] + table[a[i]][0] < dp[i - 1][1] - maxt + ch + table[a[i]][b[1]]){
            dp[i][1] = dp[i - 1][1] - maxt + ch + table[a[i]][b[1]];
            maxt = table[a[i]][b[1]];
            ch = table[a[i]][0];
        }else{
            dp[i][1] = dp[i - 1][1] + table[a[i]][0];
        }
    }
    for(int i = 2, maxt = table[a[1]][b[1]], ch = table[b[1]][0]; i <= n2; i++){
        if(dp[1][i - 1] + table[b[i]][0] < dp[1][i - 1] - maxt + ch + table[a[1]][b[i]]){
            dp[1][i] = dp[1][i - 1] - maxt + ch + table[a[1]][b[i]];
            maxt = table[a[1]][b[i]];
            ch = table[b[i]][0];
        }else{
            dp[1][i] = dp[1][i - 1] + table[b[i]][0];
        }
    }
    for(int i = 2; i <= n1; i++){
        for(int j = 2; j <= n2; j++){
            dp[i][j] = max({dp[i - 1][j - 1] + table[a[i]][b[j]], dp[i - 1][j] + table[a[i]][0], dp[i][j - 1] + table[0][b[j]]});
        }
    }
    printf("%lld", dp[n1][n2]);
    return 0;
}