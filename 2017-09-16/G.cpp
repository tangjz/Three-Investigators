#include <bits/stdc++.h>
using namespace std;
const int maxn = 50001, maxq = 500001, maxm = 231, maxd = 17;
int n, m, a[maxn], dep[maxn], mx, fa[maxd][maxn], f[maxn], g[maxn], ord[maxq], ans[maxq];
vector<int> e[maxn], seq[maxn];
struct Query {
	int u, v, stp, pp;
} que[maxq];
bool cmp(int const &x, int const &y) {
	return que[x].stp < que[y].stp;
}
void pfs(int u) {
	for(auto &v : e[u]) {
		if(v == fa[0][u])
			continue;
		dep[v] = dep[u] + 1;
		fa[0][v] = u;
		pfs(v);
	}
}
int up(int u, int dt) {
	for(int d = 0; dt > 0; dt >>= 1, ++d)
		(dt & 1) && (u = fa[d][u]);
	return u;
}
int lca(int u, int v) {
	u = up(u, dep[u] - dep[v]);
	v = up(v, dep[v] - dep[u]);
	if(u == v)
		return u;
	for(int i = mx - 1; i >= 0; --i)
		if(fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	return fa[0][u];
}
void kfs(int u) {
	g[u] = g[f[u]] ^ a[u];
	for(auto &v : e[u]) {
		if(v == fa[0][u])
			continue;
		kfs(v);
	}
}
int stk[maxn];
void dfs(int u) {
	stk[dep[u]] = u;
	for(auto &i : seq[u])
		if(i > 0) {
			int &pp = que[i].pp, &stp = que[i].stp, &ret = ans[i];
			for(int j = dep[u]; j >= dep[pp]; j -= stp)
				ret ^= a[stk[j]];
		} else if(i < 0) {
			i = -i;
			int &pp = que[i].pp, &stp = que[i].stp, &ret = ans[i];
			for(int j = dep[u]; j > dep[pp]; j -= stp)
				ret ^= a[stk[j]];
		}
	for(auto &v : e[u]) {
		if(v == fa[0][u])
			continue;
		dfs(v);
	}
}
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		for(int i = 1; i <= n; ++i) {
			vector<int>().swap(e[i]);
			vector<int>().swap(seq[i]);
		}
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		dep[0] = -1;
		dep[1] = fa[0][1] = 0;
		pfs(1);
		for(mx = 0; 1 << mx <= n; ++mx);
		for(int d = 1; d < mx; ++d)
			for(int i = 1; i <= n; ++i)
				fa[d][i] = fa[d - 1][fa[d - 1][i]];
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			f[i] = i;
		}
		int cnt = 0;
		for(int i = 1; i <= m; ++i) {
			int &u = que[i].u, &v = que[i].v, &stp = que[i].stp, &pp = que[i].pp;
			scanf("%d%d%d", &u, &v, &stp);
			pp = lca(u, v);
			int len = dep[u] + dep[v] - (dep[pp] << 1), adt = len % stp;
			if(dep[v] - dep[pp] >= adt)
				v = up(v, adt);
			else {
				v = up(u, len - adt);
				pp = v;
			}
			if(stp < maxm) {
				ord[cnt++] = i;
			} else {
				seq[u].push_back(i);
				seq[v].push_back(-i);
			}
		}
		memset(ans + 1, 0, m * sizeof(int));
		sort(ord, ord + cnt, cmp);
		for(int i = 0, j = 0; i < cnt; ++i) {
			int o = ord[i];
			if(j < que[o].stp) {
				for(int dt = que[o].stp - j, d = 0; dt > 0; dt >>= 1, ++d)
					if(dt & 1) {
						for(int u = 1; u <= n; ++u)
							f[u] = fa[d][f[u]];
						j += 1 << d;
					}
				kfs(1);
			}
			int &u = que[o].u, &v = que[o].v, &pp = que[o].pp, &stp = que[o].stp, &ret = ans[o];
			int x = up(u, ((dep[u] - dep[pp]) / stp + 1) * stp), y = up(v, ((dep[v] - dep[pp] - 1) / stp + 1) * stp);
			ret = g[u] ^ g[x] ^ (dep[pp] < dep[v] ? g[v] ^ g[y] : 0);
		}
		dfs(1);
		for(int i = 1; i <= m; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
