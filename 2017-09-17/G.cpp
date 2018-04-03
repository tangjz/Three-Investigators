#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()
#define upd(a, b) (a > b) && (a = b)

const int INF = 300;
int T, ca;
char s[211];
int f[5][203][203], fl[2], fr[3];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		memset(f, 0x3f, sizeof f);
		for(int i = 1; i <= n + 1; ++i)
			f[0][i][i - 1] = 0;
		for(int len = 1; len <= n; ++len){
			for(int i = 1; i + len - 1 <= n; ++i){
				int j = i + len - 1;
				if(s[i] == s[i - 1] || s[j] == s[j + 1]) continue;
				int &f0 = f[0][i][j];
				int &f1 = f[1][i][j];
				int &f2 = f[2][i][j];
				int &f3 = f[3][i][j];
				int &f4 = f[4][i][j];
				for(int k = i; k <= j; ++k){
					if(k > i && s[k] == s[k - 1]) continue;
                    
					int pl = i, pr = k - 1, ql = k + 1 + (s[k] == s[k + 1]), qr = j;
					int tmp = 1 + (s[k] == s[k + 1]);
					if(s[k] == '0'){
						fl[0] = f[0][pl][pr];
						fl[1] = f[1][pl][pr];
						fr[0] = f[0][ql][qr];
						fr[1] = f[1][ql][qr];
						fr[2] = f[3][ql][qr];

						if(tmp == 1){
							if(fl[0] < INF){
								(fr[0] < INF) && upd(f1, fl[0] + fr[0]);
								(fr[1] < INF) && upd(f3, fl[0] + fr[1]);
								(fr[2] < INF) && upd(f0, fl[0] + fr[2]);
							}
							if(fl[1] < INF){
								(fr[1] < INF) && upd(f0, fl[1] + fr[1]);
								(fr[2] < INF) && upd(f0, fl[1] + fr[2]);
							}
						}else{
							if(fl[0] < INF){
								(fr[0] < INF) && upd(f3, fl[0] + fr[0]);
								(fr[1] < INF) && upd(f0, fl[0] + fr[1]);
								(fr[2] < INF) && upd(f0, fl[0] + fr[2]);
							}
						}
					}else{
						fl[0] = f[0][pl][pr];
						fl[1] = f[2][pl][pr];
						fr[0] = f[0][ql][qr];
						fr[1] = f[2][ql][qr];
						fr[2] = f[4][ql][qr];
                        
						if(tmp == 1){
							if(fl[0] < INF){
								if(fr[0] < INF) upd(f2, fl[0] + fr[0]);
								if(fr[1] < INF) upd(f4, fl[0] + fr[1]);
								if(fr[2] < INF) upd(f0, fl[0] + fr[2]);
							}
							if(fl[1] < INF){
								if(fr[1] < INF) upd(f0, fl[1] + fr[1]);
								if(fr[2] < INF) upd(f0, fl[1] + fr[2]);
							}
						}else{
							if(fl[0] < INF){
								if(fr[0] < INF) upd(f4, fl[0] + fr[0]);
								if(fr[1] < INF) upd(f0, fl[0] + fr[1]);
								if(fr[2] < INF) upd(f0, fl[0] + fr[2]);
							}
						}
					}
				}
				upd(f0, f1 + 2);
				upd(f0, f2 + 2);
				upd(f0, f3 + 1);
				upd(f0, f4 + 1);
			}
		}
        
		printf("Case #%d: %d\n", ++ca, (int)f[0][1][n]);
	}
	//system("pause"); 
	return 0;
}
