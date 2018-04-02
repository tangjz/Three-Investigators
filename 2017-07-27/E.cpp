#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 3100;

int T, ans;
int N, number[NMAX];
int pref[NMAX], suff[NMAX];
int prefIgnore[NMAX], suffIgnore[NMAX];
int prefIgnoreEnd[NMAX][2], suffIgnoreEnd[NMAX][2];
int jump[NMAX][NMAX], f[NMAX][NMAX];

int main()
{
	int t;
	int i, j, l, r;
	int cnt, minimum, maximum;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		ans = 0;
		memset(jump, -1, sizeof(jump));
		memset(f, 0, sizeof(f));
		scanf("%d", &N);
		for(i = 1;i <= N;i += 1)
			scanf("%d", &number[i]);
		pref[0] = 0;
		for(i = 1, cnt = maximum = 0;i <= N;i += 1)
		{
			maximum = max(number[i], maximum);
			if(i == maximum)
				pref[i] = ++cnt;
			else
				pref[i] = -1;
		}
		suff[N + 1] = 0;
		for(i = minimum = N, cnt = 0;i;i -= 1)
		{
			minimum = min(number[i], minimum);
			if(i == minimum)
				suff[i] = ++cnt;
			else
				suff[i] = -1;
		}
		for(i = 1;i <= N;i += 1)
		{
			prefIgnore[i] = -1;
			prefIgnoreEnd[i][0] = prefIgnoreEnd[i][1] = -1;
			for(j = i, l = r = number[i];j;j -= 1)
			{
				l = min(l, number[j]);
				r = max(r, number[j]);
				if(r - l + 1 == i - j + 1 && l > j && pref[j - 1] >= 0)
				{
					prefIgnore[i] = pref[j - 1] + 1;
					prefIgnoreEnd[i][0] = l;
					prefIgnoreEnd[i][1] = r;
					break;
				}
			}
		}
		for(i = N;i;i -= 1)
		{
			suffIgnore[i] = -1;
			suffIgnoreEnd[i][0] = suffIgnoreEnd[i][1] = -1;
			for(j = i, l = r = number[i];j <= N;j += 1)
			{
				l = min(l, number[j]);
				r = max(r, number[j]);
				if(r - l + 1 == j - i + 1 && r < j && suff[j + 1] >= 0)
				{
					suffIgnore[i] = suff[j + 1] + 1;
					suffIgnoreEnd[i][0] = l;
					suffIgnoreEnd[i][1] = r;
					break;
				}
			}
		}
		for(i = 1;i <= N;i += 1)
		{
			for(j = i, l = r = number[i];j <= N;j += 1)
			{
				l = min(l, number[j]);
				r = max(r, number[j]);
				if(r - l + 1 == j - i + 1 && jump[i][l] < 0)
					jump[i][l] = j + 1;
			}
		}
		ans = pref[N];
		for(i = N;i;i -= 1)
		{
			for(j = 1;j <= N;j += 1)
			{
				f[i][j] = -1;
				if(j > suffIgnoreEnd[i][0])
					f[i][j] = suffIgnore[i];
				if(jump[i][j] >= 0 && jump[i][j] != N + 1 && f[jump[i][j]][j + jump[i][j] - i] >= 0)
					f[i][j] = max(f[i][j], f[jump[i][j]][j + jump[i][j] - i] + 1);
				if(prefIgnore[i - 1] >= 0 && f[i][j] >= 0)
				{
					ans = max(ans, prefIgnore[i - 1] + f[i][j]);
					//printf("valid\n");
				}
				//printf("f[l:%d][min:%d]:%d\n", i, j, f[i][j]);
			}
		}
		/*
		printf("pref:\n");
		for(i = 1;i <= N;i += 1)
			printf("%d%c", pref[i], " \n"[i == N?1:0]);
		printf("suff:\n");
		for(i = 1;i <= N;i += 1)
			printf("%d%c", suff[i], " \n"[i == N?1:0]);
		printf("prefIgnore:\n");
		for(i = 1;i <= N;i += 1)
			printf("%d%c", prefIgnore[i], " \n"[i == N?1:0]);
		printf("suffIgnore:\n");
		for(i = 1;i <= N;i += 1)
			printf("%d%c", suffIgnore[i], " \n"[i == N?1:0]);
		*/
		printf("%d\n", ans);
	}
	exit(0);
}
