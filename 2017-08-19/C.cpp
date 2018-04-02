#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 31;

int T, N;
int adj[NMAX][NMAX];

int main()
{
	int i, j, k, t;
	bool flag;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		flag = true;
		scanf("%d", &N);
		if(N >= 6)
		{
			for(i = 1;i <= N;i += 1)
			{
				for(j = 1;j <= N - i;j += 1)
					scanf("%*d");
			}
		}
		else
		{
			for(i = 1;i <= N;i += 1)
			{
				for(j = 1;j <= N - i;j += 1)
				{
					scanf("%d", &adj[i][i + j]);
					adj[i + j][i] = adj[i][i + j];
				}
			}
		}
		if(N >= 6)
			printf("Bad Team!\n");
		else
		{
			for(i = 1;i <= N;i += 1)
			{
				for(j = i + 1;j <= N;j += 1)
				{
					for(k = j + 1;k <= N;k += 1)
					{
						if((adj[i][j] && adj[j][k] && adj[k][i])
							|| (!adj[i][j] && !adj[j][k] && !adj[k][i]))
							flag = false;
					}
				}
			}
			if(flag)
				printf("Great Team!\n");
			else
				printf("Bad Team!\n");
		}
	}
	exit(0);
}
