#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = 503, maxm = 1001;
int n, d, r, cur, pre = 1;
DB c[maxn][maxn], f[2][maxn][maxm];
int main() {
	scanf("%d%d%d", &n, &d, &r);
	for(int i = 0; i <= n; ++i) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	f[cur][0][0] = 1;
	for(int i = d + 1; i >= 1; --i) {
		pre ^= 1;
		cur ^= 1;
		memset(f[cur], 0, sizeof f[0]);
		for(int j = 0; j <= n; ++j)
			for(int k = j; k <= n + d; ++k) {
				if(f[pre][j][k] < 1)
					continue;
				int adt = k + (r - j) * i;
				for(int x = j, y = k; x <= n && y <= n + d; ++x, y += i) {
					DB tmp = c[x][j] * f[pre][j][k];
					if(j < r && x >= r)
						tmp *= adt;
					f[cur][x][y] += tmp;
				}
			}
	}
	DB ans = f[cur][n][n + d];
	for(int i = 1; i < n; ++i)
		ans = ans * i / (d + i);
	printf("%.20f\n", ans);
	return 0;
}
