#include <bits/stdc++.h>
using namespace std;
const int maxn = 10001;
int t, n, m, tot, seq[maxn], bcc[maxn], in[maxn], out[maxn];
vector<int> e[maxn], g[maxn];
bool vis[maxn];
void pfs(int u, int p) {
	vis[u] = 1;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		if(*it != p && !vis[*it])
			pfs(*it, u);
	seq[tot++] = u;
}
void dfs(int u, int p) {
	bcc[u] = tot;
	for(vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)
		if(*it != p && bcc[*it] == -1)
			dfs(*it, u);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i) {
			vector<int>().swap(e[i]);
			vector<int>().swap(g[i]);
		}
		while(m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			--u, --v;
			e[u].push_back(v);
			g[v].push_back(u);
		}
		tot = 0;
		memset(vis, 0, n * sizeof(bool));
		for(int i = 0; i < n; ++i)
			if(!vis[i])
				pfs(i, -1);
		tot = 0;
		memset(bcc, -1, n * sizeof(int));
		for(int i = n - 1; i >= 0; --i)
			if(bcc[seq[i]] == -1) {
				in[tot] = out[tot] = 0;
				dfs(seq[i], -1);
				++tot;
			}
		for(int i = 0; i < n; ++i)
			for(vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it) {
				int j = *it;
				if(bcc[i] != bcc[j]) {
					++out[bcc[i]];
					++in[bcc[j]];
				}
			}
		int c1 = 0, c2 = 0;
		for(int i = 0; i < tot; ++i) {
			c1 += !in[i];
			c2 += !out[i];
		}
		int ans = max(c1, c2);
		if(ans == 1 && tot == 1)
			--ans;
		printf("%d\n", ans);
	}
	return 0;
}
