#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 10, MMAX = 5100, VMAX = 140;

int N, M, K, ans;
char table[MMAX][NMAX];

int allMask[MMAX], contMask[MMAX];
int single[MMAX], interval[MMAX][MMAX];
bool ban[VMAX][VMAX];

//f[t][pressMask]
int f[MMAX][VMAX], g[MMAX];
bool availableF[MMAX][VMAX], availableG[MMAX];

int getSingleScore(int t, int mask)
{
	int i, r = 0;
	for(i = 0;i < N;i += 1)
	{
		if(table[t][i] == '*' && (mask & (1<<i)))
			r += 5;
	}
	return r;
}

void handleIntervalScore()
{
	int i, l, r, combo, point;
	bool active[NMAX];
	int cnt[NMAX];
	for(r = 1;r <= M;r += 1)
	{
		combo = 0;
		point = 0;
		memset(cnt, 0, sizeof(cnt));
		for(i = 0;i < N;i += 1)
		{
			if(table[r][i] == '#')
			{
				if(r == M || table[r + 1][i] != '#')
					active[i] = true;
				else
					active[i] = false;
			}
			else
				active[i] = false;
		}
		for(l = r;l;l -= 1)
		{
			if(l < r && ban[allMask[l]][allMask[l + 1]])
				break;
			combo += 1;
			point += single[l];
			for(i = 0;i < N;i += 1)
			{
				if(active[i])
					cnt[i] += 1;
				if(l == 1 || table[l - 1][i] != '#')
				{
					point += cnt[i] * 10;
					cnt[i] = 0;
					active[i] = false;
				}
				if(l > 1 && table[l][i] != '#' && table[l - 1][i] == '#')
					active[i] = true;
			}
			if(l == 1 || !(contMask[l - 1] & contMask[l]))
				interval[l][r] = point + combo * (combo + 1) / 2 - 1;
			//printf("[%d %d]: %d\n", l, r, interval[l][r]);
		}
	}
}

void solve()
{
	int i, pi, pressMask;
	int prePressMask;
	int p;
	for(i = 1;i <= M;i += 1)
	{
		//0 <= pressMask < 2^N
		for(pressMask = 0;pressMask < (1<<N);pressMask += 1)
		{
			p = getSingleScore(i, pressMask);
			for(prePressMask = 0;prePressMask < (1<<N);prePressMask += 1)
			{
				if(i > 1)
				{
					if(ban[prePressMask][pressMask])
						continue;
					if(!availableF[i - 1][prePressMask])
						continue;
				}
				availableF[i][pressMask] = true;
				f[i][pressMask] = max(f[i][pressMask], f[i - 1][prePressMask] + p);
			}
			if(i == 1 
				|| 
				(
					!ban[allMask[i - 1]][pressMask]
					&& availableF[i - 1][1<<N] 
				)
			)
			{
				availableF[i][pressMask] = true;
				f[i][pressMask] = max(f[i][pressMask], f[i - 1][1<<N] + p);
			}
			if(availableF[i][pressMask])
				ans = max(ans, f[i][pressMask]);
			if(i == M || !availableF[i][pressMask])
				continue;
			if(ban[pressMask][allMask[i + 1]])
				continue;
			availableG[i] = true;
			g[i] = max(g[i], f[i][pressMask]);
		}
		//pressMask == 2^N
		for(pi = i - 1;pi >= 0;pi -= 1)
		{
			if(interval[pi + 1][i] < 0)
				continue;
			if(pi > 0 && !availableG[pi])
				continue;
			availableF[i][pressMask] = true;
			f[i][pressMask] = max(f[i][pressMask], g[pi] + interval[pi + 1][i]);
		}
		if(availableF[i][pressMask])
			ans = max(ans, f[i][pressMask]);
	}
}

int main()
{
	int i, j, k, x, y;
	char X[10], Y[10];
	while(scanf("%d %d %d", &N, &M, &K) != EOF)
	{
		ans = 0;
		memset(ban, 0, sizeof(ban));
		memset(allMask, 0, sizeof(allMask));
		memset(contMask, 0, sizeof(contMask));
		memset(single, 0, sizeof(single));
		memset(interval, -1, sizeof(interval));
		memset(availableF, 0, sizeof(availableF));
		memset(availableG, 0, sizeof(availableG));
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		for(i = 1;i <= K;i += 1)
		{
			scanf("%s %s", X, Y);
			for(j = x = y = 0;j < N;j += 1)
			{
				x |= (X[j] - '0')<<j;
				y |= (Y[j] - '0')<<j;
			}
			for(j = 0;j < (1<<N);j += 1)
			{
				if((j & x) != x)
					continue;
				for(k = 0;k < (1<<N);k += 1)
				{
					if((k & y) != y)
						continue;
					ban[j][k] = true;
				}
			}
		}
		for(i = 1;i <= M;i += 1)
		{
			scanf("%s", table[i]);
			for(j = 0;j < N;j += 1)
			{
				if(table[i][j] != '.')
					allMask[i] |= 1<<j;
				if(table[i][j] == '#')
					contMask[i] |= 1<<j;
				if(table[i][j] == '*')
					single[i] += 5;
			}
		}
		handleIntervalScore();
		solve();
		printf("%d\n", ans);
	}
	exit(0);
}
