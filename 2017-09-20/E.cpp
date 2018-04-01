#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 110;

int N, T;
int matrix[NMAX][NMAX];
int dir[4][4][2] = 
{
	{
		{1, 0},
		{-1, 0},
		{0, 1},
		{0, -1}
	},
	{
		{0, 1},
		{0, -1},
		{1, 0},
		{-1, 0}
	},
	{
		{1, 0},
		{0, 1},
		{-1, 0},
		{0, -1}
	},
	{
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0}
	}
};

void solve(int n, int t)
{
	int i, j, cur = 0;
	int x = 0, y = 0;
	int nx, ny;
	t -= 1;
	for(i = 1;i <= N * N;i += 1)
	{
		matrix[y][x] = i;
		if(t < 2)
		{
			for(j = 0;j < 4;j += 1)
			{
				nx = x + dir[t][j][0];
				ny = y + dir[t][j][1];
				if(nx < 0 || nx >= N
				|| ny < 0 || ny >= N
				|| matrix[ny][nx])
					continue;
				break;
			}
		}
		else
		{
			for(j = 0;j < 4;j += 1)
			{
				nx = x + dir[t][cur][0];
				ny = y + dir[t][cur][1];
				if(nx < 0 || nx >= N
				|| ny < 0 || ny >= N
				|| matrix[ny][nx])
				{
					cur = (cur + 1) % 4;
					continue;
				}
				break;
			}
		}
		x = nx;
		y = ny;
	}
}

int main()
{
	int i, j;
	scanf("%d %d", &N, &T);
	solve(N, T);
	for(i = 0;i < N;i += 1)
	{
		for(j = 0;j < N;j += 1)
			printf("%d%c", matrix[i][j], " \n"[j + 1 == N?1:0]);
	}
	exit(0);
}
