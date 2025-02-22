#include <iostream>
#include <cmath>
using namespace std;
int xf, yf, xc, yc, df, dc, c;// d-> 0,1,2,3
char s[11][11];
bool flag, ff, fc, f2, f3;
bool is_in(int x, int y){
    return (x >= 0 && y >= 0) && (x < 10 && y < 10);
}
/*int is_atboundary(int x, int y){
    if(x == 0) return 0;
    if(x == 9) return 1;
    if(y == 0) return 2;
    if(y == 9) return 3;
    return -1;
}*/
bool barr(int d, int x, int y){
    switch(d){
        case 0:
            return (s[x - 1][y] != '*') && is_in(x - 1, y);
        case 1:
            return (s[x][y + 1] != '*') && is_in(x, y + 1);
        case 2:
            return (s[x + 1][y] != '*') && is_in(x + 1, y);
        case 3:
            return (s[x][y - 1] != '*') && is_in(x, y - 1);
    }
    return 0;
}
/*double dis(){
    return sqrt((xf - xc) * (xf - xc) + (yf - yc) * (yf - yc));
}*/
bool change(int &d, int x, int y){
    if(!barr(d, x, y)){
        d = (d + 1) % 4;
        return 1;
        //change(d, x, y);
    }
    return 0;
}
void move(int d, int &x, int &y){
    switch(d){
        case 0:
            x--;
            return;
        case 1:
            y++;
            return;
        case 2:
            x++;
            return;
        case 3:
            y--;
            return;
    }
}
int main(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            cin >> s[i][j];
            if(s[i][j] == 'F') xf = i, yf = j;
            if(s[i][j] == 'C') xc = i, yc = j;
            if(s[i][j] == '*') f2 = 1;
        }
    }
    if(!f2){
        cout << 0;
        return 0;
    }
    while(1){
        ff = change(df, xf, yf);
        fc = change(dc, xc, yc);
        if(!ff) move(df, xf, yf);
        if(!fc) move(dc, xc, yc);
        c++;
        if(s[xf][yf] == 'F' && s[xc][yc] == 'C' && !df && !dc){
            break;
        }
        /*if(is_atboundary(xf, yf) == is_atboundary(xc, yc) && is_atboundary(xf, yf) > 0 && df == dc && dis() > 1){
            cout << 0;
            return 0;
        }*/
        if(c > 1000){
            cout << 0;
            return 0;
        }
        if(xf == xc && yf == yc){
            flag = 1;
            break ;
        }
    }
    if(flag) cout << c;
    else cout << 0;
    return 0;
}