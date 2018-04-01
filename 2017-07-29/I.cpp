#include <cstdio>
#include <cstring>
const int maxn = 200001, maxm = 400001, maxd = 18;
struct Edge {
	int nxt, v;
} e[maxm], g[maxm];
bool bri[maxm];
int n, m, q, tot, lnk[maxn], pre[maxn], cnt, bcc[maxn];
int tarjan(int u, int Fa) {
	int lowu = pre[u] = tot++;
	for(int it = lnk[u]; it != -1; it = e[it].nxt) {
		if(Fa == (it ^ 1))
			continue;
		int v = e[it].v;
		if(pre[v] == -1) {
			int lowv = tarjan(v, it);
			if(lowu > lowv)
				lowu = lowv;
			if(pre[u] < lowv)
				bri[it] = bri[it ^ 1] = 1;
		} else if(lowu > pre[v])
			lowu = pre[v];
	}
	return lowu;
}
int lst[maxn], dep[maxn], fa[maxd][maxn];
void pfs(int u) {
	bcc[u] = cnt;
	g[tot] = (Edge){lst[u], cnt};
	lst[u] = tot++;
	g[tot] = (Edge){lst[cnt], u};
	lst[cnt] = tot++;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		if(!bri[it] && bcc[e[it].v] == -1)
			pfs(e[it].v);
}
void dfs(int u) {
	for(int it = lst[u]; it != -1; it = g[it].nxt) {
		if(g[it].v == fa[0][u])
			continue;
		int v = g[it].v;
		dep[v] = dep[u] + 1;
		fa[0][v] = u;
		dfs(v);
	}
}
int lca(int u, int v) {
	for(int i = 0, j = dep[u] - dep[v]; j > 0; j >>= 1, ++i)
		(j & 1) && (u = fa[i][u]);
	for(int i = 0, j = dep[v] - dep[u]; j > 0; j >>= 1, ++i)
		(j & 1) && (v = fa[i][v]);
	if(u == v)
		return u;
	for(int d = maxd - 1; d >= 0; --d)
		if(fa[d][u] != fa[d][v]) {
			u = fa[d][u];
			v = fa[d][v];
		}
	return fa[0][u];
}
bool check(int u, int v, int pp, int w) {
	if(dep[w] < dep[pp])
		return 0;
	if(dep[w] <= dep[u]) {
		for(int i = 0, j = dep[u] - dep[w]; j > 0; j >>= 1, ++i)
			(j & 1) && (u = fa[i][u]);
		if(u == w)
			return 1;
	}
	if(dep[w] <= dep[v]) {
		for(int i = 0, j = dep[v] - dep[w]; j > 0; j >>= 1, ++i)
			(j & 1) && (v = fa[i][v]);
		if(v == w)
			return 1;
	}
	return 0;
}
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		tot = 0;
		memset(lnk, -1, n * sizeof(int));
		memset(bri, 0, (m << 1) * sizeof(bool));
		while(m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			--u;
			--v;
			e[tot] = (Edge){lnk[u], v};
			lnk[u] = tot++;
			e[tot] = (Edge){lnk[v], u};
			lnk[v] = tot++;
		}
		tot = 0;
		memset(pre, -1, n * sizeof(int));
		tarjan(0, -1); // connected
		tot = 0;
		cnt = n;
		memset(bcc, -1, n * sizeof(int));
		memset(lst, -1, n * sizeof(int));
		for(int i = 0; i < n; ++i)
			if(bcc[i] == -1) {
				lst[cnt] = -1;
				pfs(i);
				++cnt;
			}
		for(int i = 0; i < n; ++i)
			for(int it = lnk[i]; it != -1; it = e[it].nxt)
				if(bri[it]) {
					g[tot] = (Edge){lst[i], e[it].v};
					lst[i] = tot++;
				}
		dep[0] = 0;
		fa[0][0] = -1;
		dfs(0); // connected
		for(int d = 1; d < maxd; ++d)
			for(int i = 0; i < cnt; ++i)
				fa[d][i] = fa[d - 1][i] < 0 ? -1 : fa[d - 1][fa[d - 1][i]];
		scanf("%d", &q);
		while(q--) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			--u;
			--v;
			--w;
			if(u == v) {
				puts(u == w ? "Yes" : "No");
				continue;
			}
			int pp = lca(u, v);
			puts(check(u, v, pp, w) || check(u, v, pp, bcc[w]) ? "Yes" : "No");
		}
	}
	return 0;
}
