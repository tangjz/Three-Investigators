#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 31, maxp = 6;
const LL INF = (LL)2e18, pp[maxp] = {4LL, 27LL, 3125LL, 823543LL, 285311670611LL, 302875106592253LL};
vector<LL> e[maxn];
void dfs(int dep, LL val, int idx) {
	if(dep == maxp) {
		e[idx].push_back(val);
		return;
	}
	LL lim = INF / pp[dep];
	dfs(dep + 1, val, idx);
	while(val <= lim && idx < maxn)
		dfs(dep + 1, val *= pp[dep], idx += 1);
}
int main() {
	dfs(0, 1LL, 0);
	for(int i = 1; i < maxn; ++i)
		sort(e[i].begin(), e[i].end());
	int m;
	LL n;
	scanf("%d%lld", &m, &n);
	int sz = upper_bound(e[m].begin(), e[m].end(), n) - e[m].begin();
	printf("%d\n", sz);
	for(int i = 0; i < sz; ++i)
		printf("%lld%c", e[m][i], " \n"[i == sz - 1]);
	return 0;
}
