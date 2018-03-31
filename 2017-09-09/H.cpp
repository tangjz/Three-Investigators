#include <bits/stdc++.h>
using namespace std;
const int maxn = 10001;
int t, n, m, f[maxn];
vector<pair<int, int> > e[maxn];
int dfs(int u) {
	if(f[u] >= 0)
		return f[u];
	int &ret = f[u];
	ret = 0;
	for(vector<pair<int, int> >::iterator it = e[u].begin(); it != e[u].end(); ++it)
		ret = max(ret, dfs(it -> first) + (it -> second));
	return ret;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) {
			f[i] = -1;
			vector<pair<int, int> >().swap(e[i]);
		}
		while(m--) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			e[u].push_back(make_pair(v, w));
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			ans = max(ans, dfs(i));
		printf("%d\n", ans);
	}
	return 0;
}
