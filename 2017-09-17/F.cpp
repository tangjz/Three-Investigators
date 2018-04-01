#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 44723, maxv = (int)1e9, maxd = 1 << 17 | 1, MASK = (1 << 17) - 1;
int tot, pr[maxn], d[maxn], ot[maxn];
struct GcdTable {
	int rem[maxn];
	void parse(int n, int m) { // [gcd(i, m) == 1] for 1 <= i <= n, i is odd
		rem[1] = 1;
		for(int i = 1, tmp = m; pr[i] <= m; ++i) {
			if(d[tmp] == pr[i]) {
				rem[pr[i]] = 0;
				for(tmp /= pr[i]; d[tmp] == pr[i]; tmp /= pr[i]);
			} else {
				rem[pr[i]] = 1;
			}
		}
		for(int i = 3; i <= n; i += 2)
			if(d[i] < i)
				rem[i] = rem[d[i]] * rem[ot[i]];
	}
} GT;
inline int sqr(int x) {
	return x * x;
}
inline int isqrt(int x) {
	int y = (int)floor(sqrt(x));
	for( ; y * y <= x; ++y);
	for( ; y * y > x; --y);
	return y;
}
int t, cnt[maxd], m, a[maxd];
int main() {
	d[1] = ot[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			ot[i] = 1;
		}
		for(int j = 1, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			ot[k] = i;
			if(d[i] == pr[j])
				break;
		}
	}
	pr[tot] = maxn;
	for(int i = 3, iLim = isqrt((maxv << 1) - 1); i <= iLim; i += 2) {
		int j, jLim = isqrt((maxv << 1) - sqr(i)), A, B;
		jLim = min(jLim, i - 2);
		GT.parse(jLim, i);
		for(j = 1, A = i * j, B = (sqr(i) - sqr(j)) >> 1; j <= jLim; A += i << 1, B -= (j + 1) << 1, j += 2)
			if(GT.rem[j] == 1)
				++cnt[max(A, B) & MASK];
	}
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &m);
		int all = (1 << m) - 1;
		long long ans = 0;
		for(int i = 0; i <= all; ++i)
			scanf("%d", a + i);
		for(int i = 0; i <= MASK; ++i)
			ans += (long long)cnt[i] * a[i & all];
		printf("%I64d\n", ans);
	}
	return 0;
}
