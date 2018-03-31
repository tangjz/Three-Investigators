#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int T;
int N, M;
long long ans[60], mask[60];
int pref[60][2];

int main()
{
	int t, i, j, y, z;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		memset(mask, 0, sizeof(mask));
		memset(ans, 0, sizeof(ans));
		scanf("%d %d", &N, &M);
		for(i = 1;i <= N;i += 1)
			scanf("%d %d", &pref[i][0], &pref[i][1]);
		for(i = 1;i <= M;i += 1)
		{
			scanf("%d %d", &y, &z);
			mask[y] |= 1ll<<z;
		}
		for(i = 1;i <= N;i += 1)
			ans[pref[i][0]] |= mask[pref[i][1]];
		for(i = 0;i <= 50;i += 1)
		{
			for(j = 0;j <= 50;j += 1)
			{
				if(ans[i] & (1ll<<j))
					printf("%d %d\n", i, j);
			}
		}
		printf("\n");
	}
	exit(0);
}
