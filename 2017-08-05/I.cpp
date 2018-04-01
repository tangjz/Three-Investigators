#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxn = 1001, maxm = 1000001, maxd = 11;
int t, n, kk, m, x[maxn], y[maxn], dsu[maxn], dep[maxn], fa[maxd][maxn];
LL val[maxn];
DB ans, mx;
struct Edge {
	int u, v;
	LL w;
	bool used;
	bool operator < (Edge const &t) const {
		return w < t.w;
	}
} e[maxm];
vector<pair<int, LL> > g[maxn];
void dfs(int u) {
	for(vector<pair<int, LL> >::iterator it = g[u].begin(); it != g[u].end(); ++it) {
		int v = it -> first;
		LL w = it -> second;
		if(v != fa[0][u]) {
			val[v] = w;
			dep[v] = dep[u] + 1;
			fa[0][v] = u;
			dfs(v);
		}
	}
}
int lca(int u, int v) {
	for(int i = 0, j = dep[u] - dep[v]; j > 0; ++i, j >>= 1)
		(j & 1) && (u = fa[i][u]);
	for(int i = 0, j = dep[v] - dep[u]; j > 0; ++i, j >>= 1)
		(j & 1) && (v = fa[i][v]);
	if(u == v)
		return u;
	for(int i = maxd - 1; i >= 0; --i)
		if(fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	return fa[0][u];
}
inline LL sqr(int x) {
	return (LL)x * x;
}
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
bool dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return 0;
	if(dsu[u] < dsu[v])
		swap(u, v);
	if(dsu[u] == dsu[v])
		--dsu[v];
	dsu[u] = v;
	return 1;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &kk);
		m = 0;
		for(int i = 0; i < n; ++i) {
			scanf("%d%d", x + i, y + i);
			vector<pair<int, LL> >().swap(g[i]);
			for(int j = 0; j < i; ++j)
				e[m++] = (Edge){i, j, sqr(x[i] - x[j]) + sqr(y[i] - y[j]), 0};
		}
		sort(e, e + m);
		ans = 0;
		memset(dsu, -1, n * sizeof(int));
		for(int i = 0; i < m; ++i)
			if(dsu_merge(e[i].u, e[i].v)) {
				g[e[i].u].push_back(make_pair(e[i].v, e[i].w));
				g[e[i].v].push_back(make_pair(e[i].u, e[i].w));
				e[i].used = 1;
				ans += sqrt((DB)e[i].w);
			}
		dep[0] = 0;
		fa[0][0] = -1;
		dfs(0);
		for(int i = 1; i < maxd; ++i)
			for(int j = 0; j < n; ++j)
				fa[i][j] = fa[i - 1][j] < 0 ? -1 : fa[i - 1][fa[i - 1][j]];
		mx = 0;
		memset(dsu, -1, n * sizeof(int));
		for(int i = 0; i < m; ++i)
			if(!e[i].used) {
				int u = e[i].u, v = e[i].v, dep_pp = max(dep[lca(u, v)], 1);
				DB ww = sqrt((DB)e[i].w);
				for(u = dsu_find(u); dep_pp < dep[u]; u = dsu_find(u)) {
					mx = max(mx, ww - sqrt((DB)val[u]));
					dsu[u] = fa[0][u];
				}
				for(v = dsu_find(v); dep_pp < dep[v]; v = dsu_find(v)) {
					mx = max(mx, ww - sqrt((DB)val[v]));
					dsu[v] = fa[0][v];
				}
			}
		printf("%.2f\n", (double)((ans + mx) * kk));
	}
	return 0;
}
