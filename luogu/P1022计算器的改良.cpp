#include <cstdio>
#include <cctype>
using namespace std;
char c, alp;
int left_num, right_num;
int main(){
	int t = 0, sign = 1;
	while(c = getc(stdin)){
		if('0' <= c && c <= '9'){
			t = t * 10 + c - '0';
		}else{
			if(isalpha(c)){
				alp = c;
				left_num += (t != 0 ? (sign * t) : 1);
				t = 0;
				sign = 1;
			}else{
				right_num += (-1) * sign * t;
				t = 0;
				sign = (c == '-') ? -1 : 1;
				if(c == '=') break;
			}
		}
	}
	while(c = getc(stdin)){
		if('0' <= c && c <= '9'){
			t = t * 10 + c - '0';
		}else{
			if(isalpha(c)){
				alp = c;
				left_num += (-1) * (t != 0 ? (sign * t) : 1);
				t = 0;
				sign = 1;
			}else{
				right_num += sign * t;
				t = 0;
				sign = (c == '-') ? -1 : 1;
				if(c == EOF) break;
			}
		}
	}
	putc(alp, stdout);
	printf("=%.3lf", double(right_num) / left_num);
	return 0;
}