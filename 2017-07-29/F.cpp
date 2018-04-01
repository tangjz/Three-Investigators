#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 110, MMAX = 110;

int N, M;
int perm[MMAX][NMAX];

int main()
{
	int i, j, k;
	bool use[NMAX];
	while(scanf("%d %d", &N, &M) != EOF)
	{
		memset(perm, 0, sizeof(perm));
		for(i = 0;i < M;i += 1)
			perm[i][0] = (i % N) + 1;
		for(i = 1;i <= N;i += 1)
		{
			for(j = i - 1, k = N;j < M;j += N, k = (k - 2 + N) % N + 1)
			{
				if(k == i)
					k = (k - 2 + N) % N + 1;
				perm[j][1] = k;
			}
		}
		for(i = 0;i < M;i += 1)
		{
			memset(use, 0, sizeof(use));
			for(j = 0;j < N && perm[i][j];j += 1)
				use[perm[i][j]] = true;
			for(k = 1;j < N;j += 1)
			{
				while(use[k])
					k += 1;
				perm[i][j] = k;
				use[k] = true;
			}
		}
		for(i = 0;i < M;i += 1)
		{
			for(j = 0;j < N;j += 1)
				printf("%d%c", perm[i][j], " \n"[j + 1 == N?1:0]);
		}
	}
	exit(0);
}
