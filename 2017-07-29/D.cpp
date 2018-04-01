#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxk = 201, maxl = 5;
int n, m, s[maxn], f[maxn], cnt[2][maxk], cur, pre = 1;
long long ans;
int main() {
	int pw10[maxl];
	char buf[maxl];
	pw10[0] = 1;
	for(int i = 1; i < maxl; ++i)
		pw10[i] = pw10[i - 1] * 10;
	while(scanf("%d%d", &n, &m) == 2) {
		int pp = 1;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", s + i);
			s[n + i] = s[i];
			f[i] = f[n + i] = sprintf(buf, "%d", s[i]);
			pp = pp * pw10[f[i]] % m;
		}
		for(int i = 1; i <= (n << 1); ++i)
			s[i] = (s[i - 1] * pw10[f[i]] + s[i]) % m;
		ans = 0;
		memset(cnt[cur], 0, m * sizeof(int));
		for(int i = 1; i <= (n << 1); ++i) {
			if(i <= n) {
				++cnt[cur][s[i - 1]];
			} else {
				--cnt[cur][s[i - 1 - n] * pp % m];
			}
			pre ^= 1;
			cur ^= 1;
			memset(cnt[cur], 0, m * sizeof(int));
			int ppp = pw10[f[i]];
			for(int j = 0; j < m; ++j)
				if(cnt[pre][j])
					cnt[cur][j * ppp % m] += cnt[pre][j];
			ans += cnt[cur][s[i]];
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
