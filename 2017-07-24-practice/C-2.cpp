#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

bitset<1010> num[10], now;
int n;
char s[5000100];
int k, x;

int main(){
	while(~scanf("%d", &n)){
		for(int i = 0; i < 10; ++i) num[i] = 0;
		for(int i = 1; i <= n; ++i){
			scanf("%d", &k);
			while(k--){
				scanf("%d", &x);
				num[x][i] = 1;
			}
		}
		now = 0; now[0] = 1;
		scanf("%s", s);
		int m = strlen(s);
		for(int i = 0; i < m; ++i){
			now = (now << 1) & num[s[i] - '0'];
			now[0] = 1;
			if(now[n] == 1){
				char re = s[i + 1]; s[i + 1] = 0;
				printf("%s\n", s + (i - n) + 1);
				s[i + 1] = re;
			}			
		}
	}
	
	return 0;
}
