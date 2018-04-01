#include <cstdio>
const int maxn = 41;
int n, m, cnt[maxn], mx;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			++cnt[i + j];
	for(int i = 1; i <= n + m; ++i)
		if(mx < cnt[i])
			mx = cnt[i];
	for(int i = 1; i <= n + m; ++i)
		if(mx == cnt[i])
			printf("%d\n", i);
	return 0;
}
