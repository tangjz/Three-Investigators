#include <bits/stdc++.h>
using namespace std;
const int maxn = 101, INF = 0x3f3f3f3f;
int n, m, dis[maxn + 2][maxn + 2], pre[maxn + 2][maxn + 2], ans[maxn];
struct Edge {
	int u, v, w, msk;
} e[maxn];
bool vis[maxn];
int dsu[maxn];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return;
	if(dsu[u] < dsu[v])
		swap(u, v);
	dsu[v] -= dsu[u] == dsu[v];
	dsu[u] = v;
}
bool check(int msk) {
	memset(dsu + 1, -1, n * sizeof(int));
	for(int i = 1; i <= m; ++i)
		if(vis[i] && (e[i].msk & msk))
			dsu_merge(e[i].u, e[i].v);
	for(int i = 1; i <= n; ++i)
		if(dsu_find(1) != dsu_find(i))
			return 0;
	return 1;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		char buf[3];
		scanf("%d%d%d%s", &e[i].u, &e[i].v, &e[i].w, buf);
		e[i].msk = buf[0] == 'R' ? 1 : (buf[0] == 'G' ? 2 : 4);
		vis[i] = 1;
		if(i < m)
			ans[i] = -1;
		ans[m] += e[i].w;
	}
	if(!check(3) || !check(6))
		ans[m] = -1;
	for(int i = m; i > 1 && ans[i] != -1; --i) {
		for(int j = 1; j <= m + 2; ++j)
			for(int k = 1; k <= m + 2; ++k) {
				dis[j][k] = j == k ? 0 : INF;
				pre[j][k] = j;
			}
		for(int j = 1; j <= m; ++j)
			if(vis[j]) {
				vis[j] = 0;
				if(check(3))
					dis[m + 1][j] = -e[j].w;
				if(check(6))
					dis[j][m + 2] = 0;
				for(int k = 1; k <= m; ++k)
					if(j != k && !vis[k]) {
						vis[k] = 1;
						if(check(3))
							dis[k][j] = -e[j].w;
						if(check(6))
							dis[j][k] = e[k].w;
						vis[k] = 0;
					}
				vis[j] = 1;
			}
		for(int j = 1; j <= m + 2; ++j)
			for(int u = 1; u <= m + 2; ++u) if(dis[u][j] < INF)
				for(int v = 1; v <= m + 2; ++v) if(dis[j][v] < INF) {
					int tmp = dis[u][j] + dis[j][v];
					if(dis[u][v] > tmp) {
						dis[u][v] = tmp;
						pre[u][v] = pre[j][v];
					}
				}
		if(dis[m + 1][m + 2] < INF) {
			ans[i - 1] = ans[i] + dis[m + 1][m + 2];
			for(int u = m + 2; u != m + 1; u = pre[m + 1][u])
				if(u <= m)
					vis[u] ^= 1;
		}
	}
	for(int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
