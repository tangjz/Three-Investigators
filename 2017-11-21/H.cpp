#include<bits/stdc++.h>
using namespace std;
#define ll long long

int n, m, R;
int a[153][153];
int P[153], S[153];
int UP[153], DO[153];
int sum[153][153];
int p[153][153][153], s[153][153][153];
int cnt[153];

int main(){
	while(~scanf("%d%d%d", &n, &m, &R)){
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j){
				scanf("%d", a[i] + j);
				sum[i][j] = sum[i - 1][j] + a[i][j];
			}
		
		for(int i = 1; i <= n; ++i) UP[i] = DO[i] = -1e9;
		for(int i = 1; i <= m; ++i) P[i] = S[i] = -1e9;

		for(int U = 1; U <= n; ++U){
			for(int i = 1; i <= m; ++i) cnt[i] = 0;
			for(int D = U; D <= n; ++D){
				s[U][D][m + 1] = 0;
				for(int i = 1; i <= m; ++i) cnt[i] += a[D][i];
				
				int pre = 0, mi = 0;
				for(int i = 1; i <= m; ++i){
					pre += cnt[i];
					
					P[i] = max(P[i], pre - mi);
					UP[D] = max(UP[D], pre - mi);
					DO[U] = max(DO[U], pre - mi);
					mi = min(mi, pre);
					p[U][D][i] = pre - mi;
				}
				
				int suf = 0; mi = 0;
				for(int i = m; i >= 1; --i){
					suf += cnt[i];
					
					S[i] = max(S[i], suf - mi);
					mi = min(mi, suf);
					s[U][D][i] = suf - mi;
				}
			}
		}
		
		for(int i = 2; i <= m; ++i) P[i] = max(P[i], P[i - 1]);
		for(int i = m - 1; i >= 1; --i) S[i] = max(S[i], S[i + 1]);
		for(int i = 2; i <= n; ++i) UP[i] = max(UP[i], UP[i - 1]);
		for(int i = n - 1; i >= 1; --i) DO[i] = max(DO[i], DO[i + 1]);
		
		int ans = P[m];

		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= m; ++j){
				int now = -1e9;
				if(j > 1) now = max(now, P[j - 1]);
				if(j < m) now = max(now, S[j + 1]);
				if(i > 1) now = max(now, UP[i - 1]);
				if(i < n) now = max(now, DO[i + 1]);
				
				int re = a[i][j];
				a[i][j] = R;
				for(int U = 1; U <= i; ++U){
					int tmp = sum[i - 1][j] - sum[U - 1][j];
					for(int D = i; D <= n; ++D){
						tmp += a[D][j];
						now = max(now, tmp + p[U][D][j - 1] + s[U][D][j + 1]);
					}
				}
				a[i][j] = re;
				ans = min(ans, now);
			}
		}
		
		printf("%d\n", ans);
	}
	return 0;
}
