#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 55, MMAX = 55, CMAX = 55;

int N, M, C, ans = 2 * NMAX * MMAX;
int f[NMAX][MMAX][CMAX];
char table[NMAX][MMAX], cmd[CMAX];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q;

bool invalid(int i, int j)
{
	return i < 0 || i >= N || j < 0 || j >= M || table[i][j] == '#';
}

void update(int k)
{
	int i, j, ni, nj, t;
	int dir[][2] = {
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0}
	};
	for(i = 0;i < N;i += 1)
	{
		for(j = 0;j < M;j += 1)
			Q.push(make_pair(f[i][j][k], i * M + j));
	}
	while(!Q.empty())
	{
		i = Q.top().second / M;
		j = Q.top().second % M;
		t = Q.top().first;
		Q.pop();
		if(f[i][j][k] != t)
			continue;
		for(t = 0;t < 4;t += 1)
		{
			ni = i + dir[t][0];
			nj = j + dir[t][1];
			if(table[i][j] == 'E' || invalid(ni, nj))
				continue;
			if(f[ni][nj][k] > f[i][j][k] + 1)
			{
				f[ni][nj][k] = f[i][j][k] + 1;
				Q.push(make_pair(f[ni][nj][k], ni * M + nj));
			}
		}
	}
}

int main()
{
	int i, j, ni, nj, k;
	scanf("%d %d", &N, &M);
	for(i = 0;i < N;i += 1)
	{
		for(j = 0;j < M;j += 1)
		{
			for(k = 0;k < CMAX;k += 1)
				f[i][j][k] = 2 * NMAX * MMAX;
		}
	}
	for(i = 0;i < N;i += 1)
	{
		for(j = 0;j < M;j += 1)
		{
			scanf(" %c", &table[i][j]);
			if(table[i][j] == 'R')
			{
				table[i][j] = '.';
				f[i][j][0] = 0;
			}
		}
	}
	scanf("%s", cmd + 1);
	C = strlen(cmd + 1);
	for(k = 0;k <= C;k += 1)
	{
		update(k);
		if(k < C)
		{
			for(i = 0;i < N;i += 1)
			{
				for(j = 0;j < M;j += 1)
				{
					f[i][j][k + 1] = min(f[i][j][k + 1], f[i][j][k] + 1);
					ni = i;
					nj = j;
					switch(cmd[k + 1])
					{
						case 'U':
							ni -= 1;
							break;
						case 'D':
							ni += 1;
							break;
						case 'L':
							nj -= 1;
							break;
						case 'R':
							nj += 1;
					}
					if(table[i][j] == 'E' || invalid(ni, nj))
						f[i][j][k + 1] = min(f[i][j][k + 1], f[i][j][k]);
					else
						f[ni][nj][k + 1] = min(f[ni][nj][k + 1], f[i][j][k]);
				}
			}
		}
		else
		{
			for(i = 0;i < N;i += 1)
			{
				for(j = 0;j < M;j += 1)
				{
					if(table[i][j] == 'E')
						printf("%d\n", f[i][j][k]);
				}
			}
		}
	}
	exit(0);
}
