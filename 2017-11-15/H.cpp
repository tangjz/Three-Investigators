#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define M 21092013

const int maxn = 100005;
char s[maxn];
char sta[maxn];
int top;
int rk[maxn];
int f[maxn], L[maxn], R[maxn];

int main(){
	int T, ca = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%s", s);
		int l = strlen(s);
		top = 0;
		int ans = 0;
		for(int i = 0; i < l; ++i){
			if(s[i] == 'U'){
				if(top) --top;
			}else sta[++top] = s[i];
		}

		scanf("%s", s);
		l = strlen(s);
		
		int tot = 0;
		for(int i = 0; i < l; ++i){
			if(s[i] == 'U') rk[i] = ++tot;
		}

		int lastL = l, lastR = l;
		f[l] = L[l] = R[l] = 0;
		for(int i = l - 1; i >= 0; --i){			
			if(s[i] == 'U'){
				if(rk[i] > top) continue;
				int x = top - rk[i] + 1;
				if(sta[x] == 'L'){
					ans = (ans + f[lastR] + 1) % M;
					//printf("U %d: %d %d\n", i, lastR, f[lastR] + 1);
				}else{
					ans = (ans + f[lastL] + 1) % M;
					//printf("U %d: %d %d\n", i, lastL, f[lastL] + 1);
				}
			}else if(s[i] == 'L'){
				int x = min(lastL, lastR);
				L[i] = (L[x] + R[x] + 1) % M;
				R[i] = R[x];
				f[i] = (L[x] + R[x] + 1) % M;
				lastL = i;
				//printf("L %d: %d %d %d\n", i, L[i], R[i], f[i]);
			}else{
				int x = min(lastL, lastR);
				L[i] = L[x];
				R[i] = (L[x] + R[x] + 1) % M;
				f[i] = (L[x] + R[x] + 1) % M;
				//printf("R %d: %d %d %d\n", i, L[i], R[i], f[i]);
				lastR = i;
			}
		}
		int x = min(lastL, lastR);
		ans = (ans + L[x] + R[x] + 1) % M;
		printf("Case %d: %d\n", ++ca, ans);
	}
	return 0;
}
