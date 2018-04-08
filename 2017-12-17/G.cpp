#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e3 + 1, maxm = (int)4e3 + 1, maxs = (int)8e6 + 1;
int t, n, m, q, tot, idx[maxs], nxt[maxs][2], dep[maxn << 1 | 1], ch[maxn << 1 | 1][2], ans[maxn];
bool vis[maxn];
int pfs(int u, int depth) {
	int ret = idx[u];
	if(nxt[u][0] != -1)
		ret = pfs(nxt[u][0], depth + 1);
	if(nxt[u][1] != -1)
		if(ret == -1) {
			ret = pfs(nxt[u][1], depth + 1);
		} else {
			int tmp = pfs(nxt[u][1], depth + 1);
			dep[tot] = depth;
			ch[tot][0] = ret;
			ch[tot][1] = tmp;
			ret = tot++;
		}
	return ret;
}
int dfs(int u) {
	if(u < n)
		return vis[u];
	int lft = dfs(ch[u][0]), rht = dfs(ch[u][1]);
	if(lft && rht)
		ans[tot++] = dep[u];
	return lft + rht;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		idx[0] = nxt[0][0] = nxt[0][1] = -1;
		tot = 1;
		scanf("%d%d%d", &n, &m, &q);
		for(int i = 0; i < n; ++i) {
			static char buf[maxm];
			scanf("%s", buf);
			int rt = 0;
			for(int j = 0; j < m; ++j) {
				int o = buf[j] - '0';
				if(nxt[rt][o] == -1) {
					idx[tot] = nxt[tot][0] = nxt[tot][1] = -1;
					nxt[rt][o] = tot++;
				}
				rt = nxt[rt][o];
			}
			idx[rt] = i;
			dep[i] = m;
			ch[i][0] = ch[i][1] = -1;
		}
		tot = n;
		int rt = pfs(0, 0);
		printf("Case #%d:\n", Case);
		while(q--) {
			int c, x;
			memset(vis, 0, n * sizeof(bool));
			scanf("%d", &c);
			while(c--) {
				scanf("%d", &x);
				vis[x] = 1;
			}
			tot = 0;
			dfs(rt);
			sort(ans, ans + tot);
			tot = unique(ans, ans + tot) - ans;
			printf("%d", tot);
			for(int i = 0; i < tot; ++i)
				printf(" %d", ans[i]);
			putchar('\n');
		}
	}
	return 0;
}
