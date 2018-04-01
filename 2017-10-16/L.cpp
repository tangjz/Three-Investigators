#include <bits/stdc++.h>
using namespace std;
const int maxn = 2001;
int r, c, dsu[maxn << 1 | 1], sz[maxn << 1 | 1], ans, pos;
char buf[maxn][maxn];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : dsu[x] = dsu_find(dsu[x]);
}
void dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v) {
		++sz[v];
		return;
	}
	if(dsu[u] < dsu[v])
		swap(u, v);
	if(dsu[u] == dsu[v])
		--dsu[v];
	dsu[u] = v;
	sz[v] += sz[u] + 1;
}
int main() {
	scanf("%d%d", &r, &c);
	memset(dsu, -1, (r + c) * sizeof(int));
	for(int i = 0; i < r; ++i) {
		scanf("%s", buf[i]);
		for(int j = 0; j < c; ++j)
			if(buf[i][j] == '+')
				dsu_merge(i, r + j);
	}
	for(int i = 0; i < r; ++i)
		for(int j = 0; j < c; ++j)
			if(buf[i][j] == '.') {
				int u = dsu_find(i), v = dsu_find(r + j), w = u == v ? sz[u] : sz[u] + sz[v];
				if(ans < w) {
					ans = w;
					pos = i * c + j;
				}
			}
	printf("%d\n", ans);
	if(ans)
		printf("%d %d\n", pos / c + 1, pos % c + 1);
	return 0;
}
