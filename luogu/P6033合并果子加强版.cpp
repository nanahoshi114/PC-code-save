#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
using ll = long long;
int read(){
    int sum = 0, fl = 1;
    int ch = getchar();
    for(; !isdigit(ch); ch = getchar()){
        if(ch == '-') fl = -1;
    }
    for(; isdigit(ch); ch = getchar()){
        sum = sum * 10 + ch - '0';
    }
    return sum * fl;
}
struct queue{
    ll a[10000005];
    int l, r;
    ll front(){
        return a[l];
    }
    ll rear(){
        return a[--r];
    }
    ll size(){
        return r - l;
    }
    ll next(){
        return a[l + 1];
    }
    void push(ll x){
        a[r++] = x;
    }
    void pop(){
        l++;
    }
}que;
int i = 1, maxt;
struct map{
    ll a[100005];
    void push(int x){
        a[x]++;
    }
    void jump(){
        while(!a[i] && i <= maxt) i++;
    }
    bool empty(){
        return i > maxt;
    }
    void pop(){
        a[i]--;
        jump();
    }

}ma;
int main(){
    int n = read(), t;
    ll ans = 0;
    for(int i = 1; i <= n; i++){
        t = read();
        ma.push(t);
        maxt = max(maxt, t);
    }
    if(n == 1){
        putchar('0');
        return 0;
    }
    ma.jump();
    while(i <= maxt || que.size() > 1){
        if(!que.size()){
            que.push(i); 
            ma.pop();
            que.push(que.rear() + i);
            ma.pop();
        }else{
            if(!ma.empty()){
                if(i < que.front()){
                    que.push(i); ma.pop();
                }else{
                    que.push(que.front()); que.pop();
                }
                if((!ma.empty() && i < que.front()) || que.size() == 1){
                    que.push(que.rear() + i); ma.pop();
                }else{
                    que.push(que.rear() + que.front()); que.pop();
                }
            }else{
                que.push(que.front() + que.next());
                que.pop(); 
                que.pop();
            }
        }
        ans += que.a[que.r - 1];
    }
    printf("%lld", ans);
    return 0;
}