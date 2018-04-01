#include <cstdio>
#include <cstring>
const int maxn = 501;
int t, alen, blen, f[maxn];
char a[maxn], b[maxn];
long long ans;
int main() {
	while(scanf("%s%s", a, b) == 2) {
		alen = strlen(a);
		blen = strlen(b);
		for(int i = 1, j = 0; i < blen; ++i) {
			for( ; j && b[i] != b[j]; j = f[j]);
			f[i + 1] = b[i] == b[j] ? ++j : 0;
		}
		ans = 0;
		for(int i = 0, j = 0; i < alen; ++i)
			if(a[i] == '[') {
				int p, q, d = 0, cnt = 0;
				for(p = i; a[p] != ']'; ++p);
				for(q = p + 1; a[q] >= '0' && a[q] <= '9'; ++q)
					d = d * 10 + (a[q] - '0');
				// match a[i + 1 : p]
				for(int o = 1; o <= d; ++o) {
					for(int k = i + 1; k < p; ++k) {
						for( ; j && a[k] != b[j]; j = f[j]);
						j += a[k] == b[j];
						ans += j == blen;
					}
					cnt += p - i - 1;
					if(cnt >= blen && o < d) {
						int dt = 0;
						for(int k = i + 1; k < p; ++k) {
							for( ; j && a[k] != b[j]; j = f[j]);
							j += a[k] == b[j];
							dt += j == blen;
						}
						ans += (long long)(d - o) * dt;
						break;
					}
				}
				i = q - 1;
			} else {
				for( ; j && a[i] != b[j]; j = f[j]);
				j += a[i] == b[j];
				ans += j == blen;
			}
		printf("%I64d\n", ans);
	}
	return 0;
}
