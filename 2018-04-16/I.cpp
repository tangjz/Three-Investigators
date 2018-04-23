#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1, maxm = (int)1e3 + 1, mod = (int)1e9 + 7;
int n, m, tot, lnk[maxn], seq[maxn], out[maxn], f[maxn][maxm];
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1];
bool red[maxn];
void dfs(int u, int fa) {
	seq[tot++] = u;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		if(e[it].v != fa)
			dfs(e[it].v, u);
	out[u] = tot;
}
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		memset(lnk + 1, -1, n * sizeof(int));
		memset(red + 1, 0, n * sizeof(bool));
		for(int i = 2, fa; i <= n; ++i) {
			scanf("%d", &fa);
			e[i - 2] = (Edge){lnk[fa], i};
			lnk[fa] = i - 2;
		}
		for(int i = 1, x; i <= m; ++i) {
			scanf("%d", &x);
			red[x] = 1;
		}
		tot = 0;
		dfs(1, -1);
		memset(f, 0, sizeof f);
		f[0][0] = 1;
		for(int i = 0; i < n; ++i) {
			int nxt = out[seq[i]], adt = red[seq[i]];
			for(int j = 0; j <= m; ++j)
				if(f[i][j]) {
					mod_inc(f[i + 1][j], f[i][j]);
					mod_inc(f[nxt][j + adt], f[i][j]);
				}
		}
		for(int i = 0; i <= m; ++i)
			printf("%d\n", f[n][i]);
	}
	return 0;
}
