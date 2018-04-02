#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int T, N, ans;

int main()
{
	int t, i;
	int a, b, c, d, e, f, g;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		ans = 0;
		scanf("%d", &N);
		for(i = 0;i < N;i += 1)
		{
			scanf("%d %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f, &g);
			if(d <= a && d <= b && e <= b && e <= c && f <= c && f <= a
					&& g <= d && g <= e && g <= f
				&& d + f - g <= a && d + e - g <= b && f + e - g <= c)
				ans = max(ans, a + b + c - d - e - f + g);
		}
		printf("%d\n", ans);
	}
	exit(0);
}
