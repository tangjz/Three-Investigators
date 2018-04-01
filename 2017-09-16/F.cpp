#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 10001, mod = 998244353;
int inv[maxn], n, m, c1, c2, ans;
inline int mod_inv(int x) {
	return x < maxn ? inv[x] : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
inline int C(int n, int m) {
	int ret = 1;
	for(int i = 0; i < m; ++i)
		ret = (LL)ret * (n - i) % mod * mod_inv(i + 1) % mod;
	return ret;
}
int main() {
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	while(scanf("%d%d", &n, &m) == 2) {
		if((n & 1) != (m & 1)) {
			puts("0");
			continue;
		}
		c1 = C(n, n & 1);
		c2 = C(n >> 1, m >> 1);
		ans = 0;
		for(int i = n & 1; i <= m; i += 2) {
			ans = (ans + (LL)c1 * c2) % mod;
			if(i + 2 > m)
				break;
			c1 = (LL)c1 * (n - i) % mod * mod_inv(i + 1) % mod * (n - i - 1) % mod * mod_inv(i + 2) % mod;
			c2 = (LL)c2 * ((m - i) >> 1) % mod * mod_inv((n - i) >> 1) % mod;
		}
		if(((n - m) & 2) && ans)
			ans = mod - ans;
		printf("%d\n", ans);
	}
	return 0;
}
