#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = (int)5e3 + 1;
int n, m, a[maxn];
vector<int> p[maxm];
LL f[maxm][maxm];
LL F(int u, int v) {
	if(f[u][v])
		return f[u][v];
	LL ret = 0;
	int pL = p[u].front(), pR = p[v].back();
	int qL = p[u].size(), qR = p[v].size();
	{
		LL tmp = 0;
		for(int i = 1; i < qL; ++i)
			if(p[u][i - 1] + 1 < p[u][i])
				tmp += F(a[p[u][i - 1] + 1], a[p[u][i] - 1]);
		if(u != v)
			tmp += F(a[p[u][qL - 1] + 1], v);
		ret = max(ret, tmp);
	}
	{
		LL tmp = 0;
		if(u != v)
			tmp += F(u, a[p[v][0] - 1]);
		for(int i = 1; i < qR; ++i)
			if(p[v][i - 1] + 1 < p[v][i])
				tmp += F(a[p[v][i - 1] + 1], a[p[v][i] - 1]);
		ret = max(ret, tmp);
	}
	return f[u][v] = ret + pR - pL + 1;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		p[--a[i]].push_back(i);
	}
	printf("%lld\n", F(a[0], a[n - 1]));
	return 0;
} 
