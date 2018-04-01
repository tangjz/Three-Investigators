#include <cstdio>
typedef long long LL;
const int maxn = 100001, maxm = 4, mod = 998244353;
int f[maxn][maxm | 1], g[2][maxn][maxm | 1], cur, pre = 1;
bool mod_inc(int &x, int y) {
	return (x += y) >= mod && (x -= mod);
}
int main() {
	int t, n, sqn;
	for(sqn = 1; sqn * sqn < maxn << 1; ++sqn);
	f[0][0] = g[cur][0][0] = 1;
	for(int i = 1; i * sqn < maxn; ++i) {
		pre ^= 1;
		cur ^= 1;
		for(int j = 0; j < maxn; ++j)
			for(int k = 0; k < maxm; ++k) {
				g[cur][j][k] = 0;
				j >= i && mod_inc(g[cur][j][k], g[cur][j - i][k]);
				if(j >= sqn) {
					mod_inc(g[cur][j][k], g[pre][j - sqn][k]);
					k && mod_inc(g[cur][j][k], g[pre][j - sqn][k - 1]);
				}
				mod_inc(f[j][k], g[cur][j][k]);
			}
	}
	for(int i = 1; i < sqn; ++i)
		for(int j = i; j < maxn; ++j)
			for(int k = 0; k < maxm; ++k) {
				mod_inc(f[j][k], f[j - i][k]);
				k && mod_inc(f[j][k], f[j - i][k - 1]);
			}
	for(int i = 1; i < maxn; ++i)
		f[i][0] = (f[i][1] + 6LL * (f[i][2] + f[i][3])) % mod;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%d\n", f[n][0]);
	}
	return 0;
}
