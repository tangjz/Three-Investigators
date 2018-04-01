#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 110;

int N;
int A[NMAX][NMAX], B[NMAX][NMAX];
char ans[NMAX * NMAX];

void genA(int n)
{
	int cnt;
	int i = 0, j = 0, di = -1, dj = 1;
	int ni, nj;
	for(cnt = 0;cnt < n * n;cnt += 1)
	{
		A[i][j] = cnt;
		ni = i + di;
		nj = j + dj;
		if(0 <= ni && ni < n && 0 <= nj && nj < n)
		{
			i = ni;
			j = nj;
		}
		else if(dj < 0)
		{
			swap(di, dj);
			ni = i + 1;
			nj = j;
			if(0 <= ni && ni < n && 0 <= nj && nj < n)
			{
				i = ni;
				j = nj;
				continue;
			}
			ni = i;
			nj = j + 1;
			if(0 <= ni && ni < n && 0 <= nj && nj < n)
			{
				i = ni;
				j = nj;
				continue;
			}
		}
		else
		{
			swap(di, dj);
			ni = i;
			nj = j + 1;
			if(0 <= ni && ni < n && 0 <= nj && nj < n)
			{
				i = ni;
				j = nj;
				continue;
			}
			ni = i + 1;
			nj = j;
			if(0 <= ni && ni < n && 0 <= nj && nj < n)
			{
				i = ni;
				j = nj;
				continue;
			}
		}
	}
}

void genB(int n)
{
	int cnt;
	int i = 0, j = 0;
	int ni, nj, d = 0, pre;
	int dir[4][2] = {
		{0, 1},
		{1, 0},
		{0, -1},
		{-1, 0}
	};
	bool use[NMAX][NMAX] = {};
	for(cnt = 0;cnt < n * n;cnt += 1)
	{
		B[i][j] = cnt;
		use[i][j] = true;
		ni = i + dir[d][0];
		nj = j + dir[d][1];
		if(0 <= ni && ni < n && 0 <= nj && nj < n && !use[ni][nj])
		{
			i = ni;
			j = nj;
		}
		else
		{
			pre = d;
			d = (d + 1) % 4;
			for(;d != pre;d = (d + 1) % 4)
			{
				ni = i + dir[d][0];
				nj = j + dir[d][1];
				if(0 <= ni && ni < n && 0 <= nj && nj < n && !use[ni][nj])
					break;
			}
			i = ni;
			j = nj;
		}
	}
}

int main()
{
	int i, j;
	while(scanf("%d", &N) != EOF)
	{
		genA(N);
		genB(N);
		for(i = 0;i < N;i += 1)
		{
			for(j = 0;j < N;j += 1)
				scanf(" %c", &ans[A[i][j]]);
		}
		for(i = 0;i < N;i += 1)
		{
			for(j = 0;j < N;j += 1)
				printf("%c", ans[B[i][j]]);
			printf("\n");
		}
	}
	exit(0);
}
