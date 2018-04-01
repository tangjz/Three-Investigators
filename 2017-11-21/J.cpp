#include <bits/stdc++.h>
using namespace std;
const int maxn = 101, INF = 0x3f3f3f3f;
int n, low, upp, a[maxn], s[maxn], f[maxn][maxn][maxn];
void upd(int &x, int y) {
	y < x && (x = y);
}
int main() {
	while(scanf("%d%d%d", &n, &low, &upp) == 3) {
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			s[i] = s[i - 1] + a[i];
		}
		for(int i = 1; i <= n; ++i) {
			f[i][i][1] = 0;
			for(int j = 2; j <= upp; ++j)
				f[i][i][j] = INF;
		}
		for(int len = 2; len <= n; ++len)
			for(int L = 1, R = L + len - 1; R <= n; ++L, ++R) {
				int *cur = f[L][R], tot = s[R] - s[L - 1];
				for(int i = 1; i <= upp; ++i)
					cur[i] = INF;
				for(int k = L; k < R; ++k) {
					int *lft = f[L][k], *rht = f[k + 1][R];
					for(int i = 1; i <= upp; ++i) if(lft[i] != INF)
						for(int j = 1; i + j <= upp; ++j) if(rht[j] != INF)
							upd(cur[i + j], lft[i] + rht[j]);
				}
				for(int i = low; i <= upp; ++i)
					upd(cur[1], cur[i] + tot);
			}
		printf("%d\n", f[1][n][1] < INF ? f[1][n][1] : 0);
	}
	return 0;
}
