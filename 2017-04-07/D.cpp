#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 310, KMAX = 310, MOD = 1000000007;

int N, K;
int f[2][NMAX][KMAX][2][2];
int g[2][NMAX][KMAX][2][2];
int t[NMAX], fac[NMAX], ans;

bool trans(int *&nf, int *&ng, int i, int j, int k, int l, int m, int o)
{
	int ni, nj, nk, nl = l, nm = m;
	bool done = false;
	ni = i + 1;
	nj = j + (o == 0?1:0);
	if(i >= K)
	{
		if(k)
			k -= 1;
		else if(l && !m)
		{
			nm = 1;
			done = true;
		}
	}
	nk = k + (o == 0?1:0);
	if(o == 2)
		nl = 1;
	nf = &f[ni & 1][nj][nk][nl][nm];
	ng = &g[ni & 1][nj][nk][nl][nm];
	return done;
}

int main()
{
	int i, j, k, l, m, o, *nf, *ng;
	bool done;
	scanf("%d %d", &N, &K);
	fac[0] = 1;
	for(i = 1;i <= N;i += 1)
	{
		scanf("%d", &t[i]);
		fac[i] = (long long)fac[i - 1] * i % MOD;
	}
	sort(t + 1, t + N + 1);
	g[0][0][0][0][0] = 1;
	for(i = 0;i < N + K;i += 1)
	{
		memset(f[(i + 1) & 1], 0, sizeof(f[(i + 1) & 1]));
		memset(g[(i + 1) & 1], 0, sizeof(g[(i + 1) & 1]));
		for(j = 0;j <= i && j < N;j += 1)
		{
			for(k = 0;k <= K && k <= j;k += 1)
			{
				for(l = 0;l < 2;l += 1)
				{
					for(m = 0;m <= l;m += 1)
					{
						if(k == K && l && !m)
							continue;
						//printf("f(i:%d, j:%d, k:%d, read:%d, done:%d): %d\n", i, j, k, l, m, f[i & 1][j][k][l][m]);
						for(o = 0;o < 3 && !(o == 2 && l);o += 1)
						{
							if(N <= i && o != 1)
								continue;
							done = trans(nf, ng, i, j, k, l, m, o);
							*nf = (*nf + f[i & 1][j][k][l][m]) % MOD;
							*ng = (*ng + g[i & 1][j][k][l][m]) % MOD;
							if(done)
								*nf = (*nf + (long long)(N + 1 - (i + 1 - K)) * g[i & 1][j][k][l][m]) % MOD;
						}
					}
				}
			}
		}
	}
	t[N + 1] = 1100000;
	for(i = 1;i <= N;i += 1)
	{
		ans = (ans + (long long)t[i] * f[(N + K) & 1][i - 1][0][1][1] % MOD * fac[i - 1] % MOD * fac[N - i] % MOD) % MOD;
	}
	printf("%d\n", ans);
	exit(0);
}
