#include <cstdio>
#include <cstring>
const int mod = 95041567, maxp = 5, maxv = 49, pr[maxp] = {31, 37, 41, 43, 47};
int sei[maxp], b[maxp][maxv], c[maxv][maxv], f[maxv];
void exgcd(int a, int b, int &x, int &y) {
	if(!b) {
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
int t, n, ans;
int main() {
	for(int i = 0; i < maxp; ++i) {
		int x, y;
		exgcd(mod / pr[i], pr[i], x, y);
		sei[i] = x < 0 ? x : x + pr[i];
		c[0][0] = 1;
		for(int j = 1; j <= pr[i]; ++j) {
			b[i][j] = c[j][0] = c[j - 1][j - 1];
			for(int k = 1; k <= j; ++k)
				(c[j][k] = c[j - 1][k - 1] + c[j][k - 1]) >= pr[i] && (c[j][k] -= pr[i]);
		}
	}
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		ans = 0;
		for(int i = 0; i < maxp; ++i) {
			memcpy(f, b[i], (pr[i] + 1) * sizeof(int));
			for(int tmp = n, dep = 0; tmp > 0; tmp /= pr[i], ++dep)
				for(int j = 0, rem = tmp % pr[i]; j < rem; ++j) {
					for(int k = 0; k < pr[i]; ++k)
						f[k] = (dep * f[k] + f[k + 1]) % pr[i];
					(f[pr[i]] = f[0] + f[1]) >= pr[i] && (f[pr[i]] -= pr[i]);
				}
			ans = (ans + mod / pr[i] * sei[i] % mod * f[0]) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
