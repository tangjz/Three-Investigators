#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001, maxm = 101, maxv = 10001, maxs = 21;
int n, m, a[maxn], b[maxm], lim, f[maxv];
char s[maxs], t[maxs];
bool nxt[maxv];
int main() {
	while(scanf("%d%d%s%s", &n, &m, s, t) == 4) {
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		int r = 0, mx = 0, mn = maxm;
		for(int i = 0; i < m; ++i) {
			scanf("%d", b + i);
			r = std::__gcd(r, b[i]);
			mx = std::max(mx, b[i]);
			mn = std::min(mn, b[i]);
		}
		bool chk = 1;
		for(int i = 0; i < n; ++i) {
			if(a[i] % r) {
				chk = 0;
				break;
			}
			a[i] /= r;
		}
		if(!chk) {
			puts(t);
			continue;
		}
		mx /= r;
		mn /= r;
		for(int i = 0; i < m; ++i)
			b[i] /= r;
		lim = mx * mx + 1;
		memset(f, -1, lim * sizeof(int));
		f[0] = 0;
		for(int i = 1; i < lim; ++i)
			for(int j = 0; j < m; ++j)
				if(i >= b[j] && f[i - b[j]] != -1 && f[i] < f[i - b[j]] + 1)
					f[i] = f[i - b[j]] + 1;
		int sg = 0;
		for(int i = 0; i < n; ++i) {
			int stp = 0, pos = a[i];
			if(a[i] >= lim) {
				stp = (a[i] - lim) / mn + 1;
				pos = a[i] - stp * mn;
			}
			if(f[pos] == -1) {
				chk = 0;
				break;
			}
			sg ^= f[pos] + stp;
		}
		puts(chk && sg ? s : t);
	}
	return 0;
}
