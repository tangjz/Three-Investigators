#include <bits/stdc++.h>
using namespace std;
const int maxn = 100001;
int t, n, a[maxn], f[maxn], g[maxn], h[maxn], ans;
vector<pair<int, int> > e[maxn];
void pfs(int u, int fa) {
	f[u] = g[u] = a[u];
	h[u] = u;
	for(vector<pair<int, int> >::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = it -> first, w = it -> second;
		if(v == fa)
			continue;
		pfs(v, u);
		int tp = f[v] + w;
		if(f[u] > tp) {
			g[u] = f[u];
			f[u] = tp;
			h[u] = v;
		} else if(g[u] > tp)
			g[u] = tp;
	}
}
void dfs(int u, int fa) {
	ans = max(ans, a[u] - f[u]);
	for(vector<pair<int, int> >::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = it -> first, w = it -> second;
		if(v == fa)
			continue;
		int tp = (v == h[u] ? g[u] : f[u]) + w;
		if(f[v] > tp) {
			g[v] = f[v];
			f[v] = tp;
			h[v] = u;
		} else if(g[v] > tp)
			g[v] = tp;
		dfs(v, u);
	}
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			vector<pair<int, int> >().swap(e[i]);
		}
		for(int i = 1; i < n; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			e[u].push_back(make_pair(v, w));
			e[v].push_back(make_pair(u, w));
		}
		pfs(1, -1);
		ans = 0;
		dfs(1, -1);
		printf("%d\n", ans);
	}
	return 0;
}
