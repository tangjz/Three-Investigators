#include <set>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 300001;
int n, m, dep[maxn];
LL dt[maxn], ans;
vector<int> e[maxn];
set<pair<LL, int> > sp[maxn];
void dfs(int u, int fa) {
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(v == fa)
			continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
		for( ; !sp[v].empty() && dep[u] < dep[sp[v].begin() -> second]; sp[v].erase(sp[v].begin()));
		if(sp[v].empty()) {
			puts("-1");
			exit(0);
		}
		// determine the contribution from v (instead of u)
		int val = (sp[v].begin() -> first) + dt[v];
		ans += val;
		dt[v] -= val;
		if(sp[u].size() < sp[v].size()) {
			sp[u].swap(sp[v]);
			swap(dt[u], dt[v]);
		}
		for(set<pair<LL, int> >::iterator it = sp[v].begin(); it != sp[v].end(); ++it)
			sp[u].insert(make_pair((it -> first) + dt[v] - dt[u], it -> second));
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	while(m--) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		sp[u].insert(make_pair((LL)w, v));
	}
	dfs(1, -1);
	printf("%I64d\n", ans);
	return 0;
}
