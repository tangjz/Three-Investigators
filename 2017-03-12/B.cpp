#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 27, maxm = 51;
int m, typ[maxm], res[maxm], dsu[maxn], dis[maxn];
char op[maxm][3];
bool vis[maxn];
int dsu_find(int u)
{
	if(dsu[u] < 0)
		return u;
	int tp = dsu[u];
	dsu[u] = dsu_find(dsu[u]);
	dis[u] ^= dis[tp];
	return dsu[u];
}
bool dsu_merge(int u, int v, int w)
{
	int x = dsu_find(u);
	int y = dsu_find(v);
	if(x == y)
		return !(dis[u] ^ dis[v] ^ w);
	if(dsu[x] > dsu[y])
		swap(x, y);
	if(dsu[x] == dsu[y])
		--dsu[x];
	dsu[y] = x;
	dis[y] = dis[u] ^ dis[v] ^ w;
	return 1;
}
bool solve()
{
	memset(dsu, -1, sizeof dsu);
	memset(dis, 0, sizeof dis);
	for(int i = 0; i < m; ++i)
	{
		int tot = 0, seq[2];
		for(int j = 0; j < 2; ++j)
			if(!vis[op[i][j] - 'A'])
				seq[tot++] = op[i][j] - 'A';
		if(tot < res[i])
			return 0;
		if(!tot)
			continue;
		if(res[i] == tot)
		{
			for(int j = 0; j < tot; ++j)
				if(!dsu_merge(seq[j], maxn - 1, typ[i] == 2))
					return 0;
		}
		else if(!res[i])
		{
			for(int j = 0; j < tot; ++j)
				if(!dsu_merge(seq[j], maxn - 1, typ[i] != 2))
					return 0;
		}
		else // if(res[i] == 1)
		{
			if(!dsu_merge(seq[0], seq[1], 1))
				return 0;
		}
	}
	return 1;
}
int dfs(int dep, int low)
{
	if(dep == 3)
		return solve();
	int ret = 0;
	for( ; low < maxn - 1; ++low)
	{
		vis[low] = 1;
		ret += dfs(dep + 1, low + 1);
		vis[low] = 0;
	}
	return ret;
}
int main()
{
	scanf("%d", &m);
	for(int i = 0; i < m; ++i)
		scanf("%s%d%d", op[i], typ + i, res + i);
	printf("%d\n", dfs(0, 0));
	return 0;
}
