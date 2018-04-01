#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2001, mod = ~0u >> 1;
int n, perm[maxn], f[2][maxn], cur, pre = 1;
inline void mod_inc(int &x, int y)
{
	if((x += y - mod) < 0)
		x += mod;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i <= n; ++i)
		scanf("%d", perm + i);
	f[cur][0] = 1;
	for(int i = 2; i <= n; ++i)
	{
		cur ^= 1;
		pre ^= 1;
		memset(f[cur], 0, sizeof f[0]);
		for(int j = 0; j < i - 1; ++j)
		{
			if(!f[pre][j])
				continue;
			if((perm[j] - perm[i - 1]) * (perm[i] - perm[i - 1]) > 0)
				mod_inc(f[cur][i - 1], f[pre][j]);
			if((perm[i - 1] - perm[j]) * (perm[i] - perm[j]) > 0)
				mod_inc(f[cur][j], f[pre][j]);
		}
	}
	int ans = 0;
	for(int i = 0; i < n; ++i)
		mod_inc(ans, f[cur][i]);
	printf("%d\n", ans);
	return 0;
}
