#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ull unsigned long long
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 2000010;
int T, Q, ty;
int n, m;
int allk;
char s[maxn * 2], ss[4][maxn * 2], a[4][maxn * 2];
int bg[maxn * 2], bg_s[4][maxn * 2], bg_[4][maxn * 2];
int w[5][maxn * 2];
int len[maxn];
int ans[maxn];
int lim[maxn];
ull p[5][maxn];
int l[maxn][5], r[maxn][5];

bool cmp(const int i, const int j){
	return strcmp(ss[allk] + bg_s[allk][i], ss[allk] + bg_s[allk][j]) < 0;
}

bool cmp1(const int i, const int j){
	return bg[i + 1] - bg[i] < bg[j + 1] - bg[j];
}

int main(){
	scanf("%d", &T);
	while(T--){
		n = m = 0;
		scanf("%d", &Q);
		while(Q--){
			scanf("%d", &ty);
			if(ty == 1){
				scanf("%s", s + bg[n]);
				bg[n + 1] = bg[n] + strlen(s + bg[n]) + 1;
				int md = strlen(s + bg[n]) >> 1;
				bg_s[0][n + 1] = bg_s[0][n] + md + 1;
				bg_s[1][n + 1] = bg_s[1][n] + md + 1;
				bg_s[2][n + 1] = bg_s[2][n] + md + 1;
				bg_s[3][n + 1] = bg_s[3][n] + md + 1;
				for(int i = 0; i < md; ++i){
					ss[0][i + bg_s[0][n]] = s[i + bg[n]];
					ss[1][i + bg_s[1][n]] = s[md - i - 1 + bg[n]];
					ss[2][i + bg_s[2][n]] = s[i + bg[n] + md];
					ss[3][i + bg_s[3][n]] = s[md - i - 1 + bg[n] + md];
				}
				++n;
			}else{
				for(int j = 0; j < 4; ++j){
					scanf("%s", a[j] + bg_[j][m]);
					bg_[j][m + 1] = bg_[j][m] + strlen(a[j] + bg_[j][m]) + 1;
					if(j & 1)
						reverse(a[j] + bg_[j][m], a[j] + bg_[j][m + 1] - 1);
				}
				len[m] = max(strlen(a[0] + bg_[0][m]) + strlen(a[1] + bg_[1][m]), strlen(a[2] + bg_[2][m]) + strlen(a[3] + bg_[3][m]));
				ans[m] = 0;
				lim[m] = n - 1;
				++m;
			}
		}
		for(int i = 0; i < 4; ++i){
			for(int j = 0; j < n; ++j) w[i][j] = j;
			allk = i;
			sort(w[i], w[i] + n, cmp);
		}
		for(int j = 0; j < n; ++j) w[4][j] = j;
		sort(w[4], w[4] + n, cmp1);
		
		for(int j = 0; j < m; ++j){
			for(int k = 0; k < 4; ++k){
				for(int l = bg_[k][j]; l < bg_[k][j + 1]; ++l)
					ss[k][bg_s[k][n] + l - bg_[k][j]] = a[k][l];
				allk = k;
				l[j][k] = lower_bound(w[k], w[k] + n, n, cmp) - w[k];
				ss[k][bg_s[k][n] + bg_[k][j + 1] - bg_[k][j] - 1] = 'z' + 1;
				ss[k][bg_s[k][n] + bg_[k][j + 1] - bg_[k][j]] = 0;
				r[j][k] = upper_bound(w[k], w[k] + n, n, cmp) - w[k];
			}
			l[j][4] = -1, r[j][4] = n;
			while(l[j][4] + 1 < r[j][4]){
				int d = (l[j][4] + r[j][4] + 1) >> 1;
				if(bg[w[4][d] + 1] - bg[w[4][d]] - 1 >= len[j] << 1) r[j][4] = d;
				else l[j][4] = d;
			}
		}

		for(int i = 0; i < n; i += 64){
			for(int k = 0; k < 5; ++k){
				ull now = 0;
				for(int j = 0; j < n; ++j){
					if(w[k][j] >= i && w[k][j] < i + 64)
						now |= 1ULL << (w[k][j] - i);
					p[k][j] = now;
				}
			}
			
			for(int j = 0; j < m; ++j){
				ull sum = 0;
				if(lim[j] < i) continue;
				for(int k = 0; k < 4; ++k){
					ull x = !r[j][k] ? 0 : (!l[j][k] ? p[k][r[j][k] - 1] : p[k][r[j][k] - 1] ^ p[k][l[j][k] - 1]);
					sum = k ? (sum & x) : x;
				}
				if(l[j][4] != -1) sum &= p[4][n - 1] ^ p[4][l[j][4]];
				if(lim[j] < i + 63)
					sum &= (1ULL << (lim[j] - i + 1)) - 1;
				//printf("sum = %llu\n", sum);
				ans[j] += __builtin_popcountll(sum);
			}
		}

		for(int i = 0; i < m; ++i)
			printf("%d\n", ans[i]);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
