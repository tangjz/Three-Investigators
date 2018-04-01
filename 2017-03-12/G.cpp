#include <cstdio>
const int maxn = 1001, maxs = 11;
int n, m, q, a[maxn], f[maxn], ans;
int main()
{
	scanf("%d%d", &q, &m);
	while(q--)
	{
		scanf("%d", &n);
		for(int i = n - 1; i >= 0; --i)
			scanf("%d", a + i);
		f[n] = 0;
		for(int i = n - 1; i >= 0; --i)
		{
			bool ban[maxs] = {};
			for(int j = 0; j <= m && i + j < n; ++j)
				if(i + j + a[i + j] <= n)
					ban[f[i + j + a[i + j]]] = 1;
			for(f[i] = 0; ban[f[i]]; ++f[i]);
		}
		ans ^= f[0];
	}
	puts(ans ? "Alice can win." : "Bob will win.");
	return 0;
}
