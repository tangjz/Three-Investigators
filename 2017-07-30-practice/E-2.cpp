#include <cstdio>
#include <cstring>
const int maxn = 100001;
int n, m, idx[maxn], dsu[maxn], cnt[maxn];
long long sum[maxn];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		for(int i = 1; i <= n; ++i) {
			idx[i] = i;
			dsu[i] = -1;
			cnt[i] = 1;
			sum[i] = i;
		}
		while(m--) {
			int typ, u, v, x, y;
			scanf("%d%d", &typ, &u);
			x = dsu_find(idx[u]);
			if(typ != 3) {
				scanf("%d", &v);
				y = dsu_find(idx[v]);
			}
			if(typ == 1) {
				if(x == y)
					continue;
				if(dsu[x] == dsu[y]) {
					--dsu[x];
					dsu[y] = x;
					cnt[x] += cnt[y];
					sum[x] += sum[y];
				} else if(dsu[x] < dsu[y]) {
					dsu[y] = x;
					cnt[x] += cnt[y];
					sum[x] += sum[y];
				} else {
					dsu[x] = y;
					cnt[y] += cnt[x];
					sum[y] += sum[x];
				}
			} else if(typ == 2) {
				if(x == y)
					continue;
				if(dsu[u] != -1)
					idx[u] = ++n;
				dsu[idx[u]] = y;
				if(dsu[y] == -1)
					--dsu[y];
				--cnt[x];
				sum[x] -= u;
				++cnt[y];
				sum[y] += u;
			} else {
				printf("%d %lld\n", cnt[x], sum[x]);
			}
		}
	}
	return 0;
}
