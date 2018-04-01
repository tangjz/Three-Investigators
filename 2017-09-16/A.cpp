#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int maxn = 3001, maxq = 30001, maxd = 64, mod = 19260817;
int n, m, dsu[maxn], pw19[maxd + 1], pw26[maxd + 1];
bool vis[maxn];
ULL sd, I[maxd + 1], tmp[maxd + 1], res[maxd + 1];
ULL mat[maxn][maxd + 1], up[maxn][maxd + 1], down[maxn][maxd + 1];
vector<int> e[maxn], g[maxn], seq[maxn];
struct Query {
	int u, v, ans;
} que[maxq];
inline bool mat_eq(ULL a[], ULL b[]) { // chk a == b
	for(int i = 0; i < maxd; ++i)
		if(a[i] != b[i])
			return 0;
	return 1;
}
inline void mat_mul(ULL a[], ULL b[], ULL c[]) { // c = a * b
	memset(tmp, 0, maxd * sizeof(ULL));
	for(int i = 0; i < maxd; ++i)
		for(int j = 0; j < maxd; ++j)
			if((a[i] >> j) & 1)
				tmp[i] ^= b[j];
	memcpy(c, tmp, maxd * sizeof(ULL));
}
int dsu_find(int x) {
	if(x == dsu[x])
		return x;
	int p = dsu[x];
	dsu[x] = dsu_find(dsu[x]);
	if(!mat_eq(up[p], I))
		mat_mul(up[x], up[p], up[x]);
	if(!mat_eq(down[p], I))
		mat_mul(down[p], down[x], down[x]);
	return dsu[x];
}
void dfs(int u) {
	for(auto &i : g[u]) {
		int v = que[i].u == u ? que[i].v : que[i].u;
		if(vis[v]) {
			int x = dsu_find(v);
			// printf("add query %d to node %d\n", i, x);
			seq[x].push_back(i);
		}
	}
	vis[u] = 1;
	for(auto &v : e[u]) {
		if(vis[v])
			continue;
		dfs(v);
		// printf("merge %d -> %d\n", v, u);
		dsu[v] = u;
		memcpy(up[v], mat[v], maxd * sizeof(ULL));
		memcpy(down[v], mat[v], maxd * sizeof(ULL));
	}
	// printf("solve at %d\n", u);
	for(auto &i : seq[u]) {
		int x = que[i].u, y = que[i].v, &ans = que[i].ans;
		dsu_find(x);
		dsu_find(y);
		// printf("check %d -> %d\n", x, y);
		mat_mul(up[x], mat[u], res);
		mat_mul(res, down[y], res);
		ans = 0;
		for(int j = 0; j < maxd; ++j) {
			int sum = 0;
			for(int k = 0; k < maxd; ++k)
				if((res[j] >> k) & 1)
					(sum += pw26[k + 1]) >= mod && (sum -= mod);
			ans = (ans + (ULL)pw19[j + 1] * sum) % mod;
		}
	}
}
int main() {
	pw19[0] = pw26[0] = 1;
	for(int i = 0; i < maxd; ++i) {
		I[i] = 1ULL << i;
		pw19[i + 1] = 19ULL * pw19[i] % mod;
		pw26[i + 1] = 26ULL * pw26[i] % mod;
	}
	while(scanf("%d%d", &n, &m) == 2) {
		for(int i = 1; i <= n; ++i) {
			dsu[i] = i;
			vis[i] = 0;
			memcpy(up[i], I, maxd * sizeof(ULL));
			memcpy(down[i], I, maxd * sizeof(ULL));
			vector<int>().swap(e[i]);
			vector<int>().swap(g[i]);
			vector<int>().swap(seq[i]);
		}
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		scanf("%llu", &sd);
		for(int i = 1; i <= n; ++i) {
			memset(mat[i], 0, maxd * sizeof(ULL));
			for(int j = 0; j < maxd; ++j) {
				sd ^= sd * sd + 15;
				mat[i][j] = sd;
			}
		}
		for(int i = 0; i < m; ++i) {
			int &u = que[i].u, &v = que[i].v, &ans = que[i].ans;
			scanf("%d%d", &u, &v);
			if(u != v) {
				g[u].push_back(i);
				g[v].push_back(i);
			} else {
				ans = 0;
				for(int j = 0; j < maxd; ++j) {
					int sum = 0;
					for(int k = 0; k < maxd; ++k)
						if((mat[u][j] >> k) & 1)
							(sum += pw26[k + 1]) >= mod && (sum -= mod);
					ans = (ans + (ULL)pw19[j + 1] * sum) % mod;
				}
			}
		}
		dfs(1);
		for(int i = 0; i < m; ++i)
			printf("%d\n", que[i].ans);
	}
	return 0;
}
