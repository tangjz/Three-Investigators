#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 100001;
int n, m, col[maxn], las[maxn], tim[maxn], cir[maxn], cnt[maxn];
LL ans[maxn];
vector<int> e[maxn], g[maxn];
double out[maxn];
void dfs(int u, int c) {
	col[u] = c;
	for(vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)
		dfs(*it, c);
}
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		for(int i = 1; i <= n; ++i) {
			col[i] = i;
			las[i] = 0;
			ans[i] = 0;
			cir[i] = 0;
			tim[i] = 0;
		}
		while(m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		for(int i = 1; i <= n; ++i)
			for(vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it)
				col[*it] = col[i];
		m = 0;
		for(int i = 1; i <= n; ++i) {
			// printf("col %d: %d\n", i, col[i]);
			int j, k;
			for(j = i; !tim[j]; tim[j] = i, j = col[j]);
			if(tim[j] != i)
				continue;
			cir[j] = ++m;
			cnt[m] = 1;
			for(k = col[j]; k != j && tim[k] == i; cir[k] = m, k = col[k], ++cnt[m]);
		}
		for(int i = 1; i <= n; ++i) {
			if(!cir[i])
				g[col[i]].push_back(i);
			col[i] = -1;
		}
		for(int i = 1; i <= n; ++i)
			if(cir[i])
				dfs(i, cir[i]);
		for(int i = 1; i <= n; ++i)
			assert(col[i] != -1);
		for(int i = 1; i <= n; ++i)
			for(vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it) {
				int j = *it;
				if(col[j] != col[i]) {
					ans[col[j]] += i - las[j];
					col[j] = col[i];
					las[j] = i;
				}
			}
		for(int i = 1; i <= n; ++i)
			ans[col[i]] += n - las[i];
//		for(int i = 1; i <= n; ++i) {
//			printf("%d: %I64d\n", i, ans[i]);
//		}
		m = 0;
		for(int i = 1; i <= n; ++i)
			if(ans[cir[i]])
				out[++m] = ans[cir[i]] / (double)((LL)cnt[cir[i]] * n);
		sort(out + 1, out + m + 1);
		for(int i = m; i >= 1; --i)
			printf("%.6f\n", out[i]);
		for(int i = 1; i <= n; ++i) {
			vector<int>().swap(e[i]);
			vector<int>().swap(g[i]);
		}
	}
	return 0;
}
