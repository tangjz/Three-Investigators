#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 110, MOD = 1000000007;

int T, ans;
int N, K;
int f[NMAX][NMAX];
int pre[NMAX], must[NMAX], maxPos[NMAX];

int main()
{
	int t, i, j, k, cnt;
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		ans = 0;
		memset(f, 0, sizeof(f));
		memset(must, -1, sizeof(must));
		scanf("%d %d", &N, &K);
		for(i = 1;i <= K;i += 1)
			scanf("%d", &pre[i]);
		for(i = 1;i <= K;i += 1)
		{
			for(j = 1, cnt = 0;j < i;j += 1)
			{
				if(pre[j] < pre[i])
					cnt += 1;
			}
			must[pre[i]] = pre[i] - 1 - cnt;
		}
		for(i = 1;i <= N;i += 1)
			maxPos[i] = i - 1;
		for(i = 1;i <= K;i += 1)
		{
			for(j = i + 1;j <= N;j += 1)
			{
				if(must[j] < 0)
					maxPos[j] -= 1;
			}
		}
		f[0][0] = 1;
		for(i = 0;i < N;i += 1)
		{
			for(j = 0;j <= i;j += 1)
			{
				for(k = 0;k <= j && k <= maxPos[i + 1];k += 1)
				{
					if(must[i + 1] < 0 || must[i + 1] == k)
						(f[i + 1][k?k:j + 1] += f[i][j]) %= MOD;
				}
			}
		}
		for(i = 0;i <= N;i += 1)
			(ans += f[N][i]) %= MOD;
		printf("Case #%d: %d\n", t, ans);
	}
	exit(0);
}
