#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 110, MMAX = 110;

int N, M;
int D[NMAX];
int f[NMAX][NMAX][MMAX];
bool visit[NMAX][NMAX][MMAX];

void update(int i, int j, int k, int v)
{
	if(!visit[i][j][k])
		f[i][j][k] = v;
	else
		f[i][j][k] = max(f[i][j][k], v);
	visit[i][j][k] = true;
}

int main()
{
	int i, j, k;
	while(scanf("%d %d", &N, &M) != EOF)
	{
		memset(visit, 0, sizeof(visit));
		for(i = 0;i < N;i += 1)
			scanf("%d", &D[i]);
		D[N] = 0;
		visit[1][0][M] = true;
		for(i = 1;i <= N;i += 1)
		{
			for(j = 0;j <= i;j += 1)
			{
				for(k = 0;k <= M;k += 1)
				{
					if(!visit[i][j][k])
						continue;
					//printf("i:%d j:%d k:%d: %d\n", i, j, k, f[i][j][k]);
					if(k)
					{
						update(i + 1, j + 1, k - 1, f[i][j][k] + D[i] * (2 * j + 2) + D[0]);
						if(j)
						{
							update(i + 1, j, k - 1, f[i][j][k] + D[i] * 2 * j);
							update(i + 1, j - 1, k - 1, f[i][j][k] + D[i] * (2 * j - 2) + D[0]);
						}
					}
					update(i + 1, j, k, f[i][j][k] + D[i] * 2 * j);
				}
			}
		}
		printf("%d\n", f[N + 1][0][0]);
	}
	exit(0);
}
