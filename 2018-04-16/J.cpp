#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, INF = 0x3f3f3f3f;
int n, m, fa[maxn], cov[maxn], fbd[8], f[maxn][2][3][8], g[2][8];
vector<int> e[maxn];
bool vis[maxn];
void upd(int &x, int y) {
	x > y && (x = y);
}
bool dfs(int u) {
	// construct
	vis[u] = 1;
	for(auto v : e[u])
		if(v == fa[u]) {
			;
		} else if(fa[v] == -1) {
			fa[v] = u;
			if(!dfs(v))
				return 0;
		} else if(vis[v]) {
			++m;
			for(int tp = u; tp != v; tp = fa[tp])
				if(cov[tp] == -1) {
					cov[tp] = m;
				} else {
					return 0;
				}
		}
	vis[u] = 0;
	// processing
	int cur = 0, pre = 1, sp = -1;
	memset(g[cur], 0x3f, sizeof g[0]);
	g[cur][0] = 0; // g[cur][cmsk]
	for(auto v : e[u]) {
		if(fa[v] != u)
			continue;
		if(cov[v] != -1 && cov[v] == cov[u]) {
			sp = v;
			continue;
		}
		pre ^= 1;
		cur ^= 1;
		memset(g[cur], 0x3f, sizeof g[0]);
		for(int msk = 0; msk < 8; ++msk) {
			for(int i = 0; i < 3; ++i) {
				if((fbd[msk] >> i) & 1)
					continue;
				int msk2 = msk | 1 << i;
				if(cov[v] == -1) {
					upd(g[cur][msk2], g[pre][msk] + f[v][0][i][0]);
				} else {
					for(int j = 0; j < 3; ++j) {
						if((fbd[msk2] >> j) & 1)
							continue;
						int msk3 = msk2 | 1 << j;
						for(int k = 0; k < 8; ++k)
							if(!((fbd[k] >> j) & 1))
								upd(g[cur][msk3], g[pre][msk] + f[v][(j + 1) & 1][i][k] + j);
					}
				}
			}
		}
	}
	memset(f[u], 0x3f, sizeof f[0]);
	if(cov[u] == -1) {
		for(int msk = 0; msk < 8; ++msk)
			for(int i = 0; i < 3; ++i)
				if(!((fbd[msk] >> i) & 1))
					upd(f[u][0][i][0], g[cur][msk] + i);
	} else {
		for(int msk = 0; msk < 8; ++msk)
			for(int i = 0; i < 3; ++i) {
				if((fbd[msk] >> i) & 1)
					continue;
				int msk2 = msk | 1 << i;
				if(sp == -1) {
					upd(f[u][i & 1][i][msk2], g[cur][msk] + i);
				} else {
					for(int j = 0; j < 3; ++j) {
						if((fbd[msk2] >> j) & 1)
							continue;
						for(int k = 0; k < 8; ++k) {
							upd(f[u][i & 1][i][k], g[cur][msk] + f[sp][0][j][k] + i);
							upd(f[u][(i + 1) & 1][i][k], g[cur][msk] + f[sp][1][j][k] + i);
						}
					}
				}
			}
	}
	return 1;
}
int main() {
	for(int i = 0; i < 8; ++i)
		fbd[i] = (i & 1) << 1 | (i & 2) >> 1 | (i & 4);
	while(scanf("%d%d", &n, &m) == 2) {
		while(m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		memset(fa + 1, -1, n * sizeof(int));
		memset(cov + 1, -1, n * sizeof(int));
		m = 0;
		int ans = 0;
		for(int u = 1; u <= n && ans < INF; ++u) {
			if(fa[u] != -1)
				continue;
			fa[u] = 0;
			if(!dfs(u)) {
				ans = INF;
			} else {
				int res = INF;
				for(int i = 0; i < 3; ++i)
					if(f[u][0][i][0] < INF)
						upd(res, f[u][0][i][0] - i);
				ans = min(ans + res, INF);
			}
		}
		printf("%d\n", ans < INF ? ans : -1);
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
	}
	return 0;
}
