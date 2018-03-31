#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 101;
int tot, t;
LL f[maxn], n;
int main() {
	f[1] = 1;
	for(tot = 2; f[tot - 1] <= (LL)1e16; ++tot)
		f[tot] = f[tot - 1] * 6 - f[tot - 2] + 2;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%lld", &n);
		printf("Case #%d: %lld\n", Case, *std::lower_bound(f, f + tot, n));
	}
	return 0;
}
