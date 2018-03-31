#include <cstdio>
#include <algorithm>
const int maxn = 501;
int t, n, e[maxn][maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			e[i][i] = 0;
		if(n & 1) {
			int k = n >> 1, m = k << 1;
			for(int dt = 0; dt < k; ++dt) {
				int las = n - 1, cur;
				for(int i = 0; i < m; ++i) {
					if(i & 1)
						cur = (dt - ((i + 1) >> 1)) % m;
					else
						cur = (dt + (i >> 1)) % m;
					if(cur < 0)
						cur += m;
					e[las][cur] = e[cur][las] = (i + dt) & 1 ? 1 : 2;
					las = cur;
				}
				cur = n - 1;
				e[las][cur] = e[cur][las] = (m + dt) & 1 ? 1 : 2;
			}
		} else {
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
					if(i != j)
						e[i][j] = (i < (n >> 1)) == (j < (n >> 1)) ? 1 : 2;
		}
		int ans = n * (n - 1) * (n - 2) / 3;
		for(int i = 0; i < n; ++i) {
			int deg = 0;
			for(int j = 0; j < n; ++j)
				deg += e[i][j] == 1;
			ans -= deg * (n - 1 - deg);
		}
		ans /= 2;
		printf("%d\n", ans);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				printf("%d%c", e[i][j], " \n"[j == n - 1]);
	}
	return 0;
}
