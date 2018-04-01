#include <cstdio>
#include <cstring>
const int maxn = 100001, maxv = 27;
int n, m, v, a[maxn], b[maxn], f[maxn], las, ans;
int bit[maxv], cnt[maxv], rk[maxn], eq[maxn];
inline void bit_add(int x, int y) {
	cnt[x] += y;
	for( ; x <= v; x += x & -x)
		bit[x] += y;
}
inline void bit_que(int x, int &rk, int &eq) {
	eq = cnt[x];
	rk = 0;
	for( ; x > 0; x -= x & -x)
		rk += bit[x];
}
inline bool match(int x, int rk, int eq) {
	int rk2, eq2;
	bit_que(x, rk2, eq2);
	return rk == rk2 && eq == eq2;
}
int main() {
	while(scanf("%d%d%d", &n, &m, &v) == 3) {
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		for(int i = 0; i < m; ++i)
			scanf("%d", b + i);
		memset(bit + 1, 0, v * sizeof(int));
		memset(cnt + 1, 0, v * sizeof(int));
		for(int i = 0; i < m; ++i) {
			bit_add(b[i], 1);
			bit_que(b[i], rk[i], eq[i]);
		}
		memset(bit + 1, 0, v * sizeof(int));
		memset(cnt + 1, 0, v * sizeof(int));
		for(int i = 1, j = 0; i < m; ++i) {
			bit_add(b[i], 1);
			for( ; j && !match(b[i], rk[j], eq[j]); j = f[j])
				for(int k = i - j; k < i - f[j]; ++k)
					bit_add(b[k], -1);
			f[i + 1] = match(b[i], rk[j], eq[j]) ? ++j : 0;
		}
		las = -1, ans = 0;
		memset(bit + 1, 0, v * sizeof(int));
		memset(cnt + 1, 0, v * sizeof(int));
		for(int i = 0, j = 0; i < n; ++i) {
			bit_add(a[i], 1);
			for( ; j && !match(a[i], rk[j], eq[j]); j = f[j])
				for(int k = i - j; k < i - f[j]; ++k)
					bit_add(a[k], -1);
			if((j += match(a[i], rk[j], eq[j])) == m) {
				if(i - las >= m) {
					++ans;
					las = i;
				}
				for(int k = i - j + 1; k <= i - f[j]; ++k)
					bit_add(a[k], -1);
				j = f[j];
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
