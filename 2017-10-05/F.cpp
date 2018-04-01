#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 210;

int N, M, tot, mod;
int sol[NMAX][NMAX][2];
bool use[NMAX][NMAX];

void insert(int edge[][2], int x, int y)
{
	int id;
	use[x][y] = use[y][x] = true;
	id = (edge[0][0] += 1);
	edge[id][0] = x + 1;
	edge[id][1] = y + 1;
}

void construct()
{
	int i, j, k, base = 0, cur, nxt;
	for(i = 0;;i += 2, base = (base - 1 + mod) % mod)
	{
		if(use[base][2 * N - 1])
			break;
		insert(sol[i], base, 2 * N - 1);
		for(j = 1, cur = base;j < N;j += 1)
		{
			nxt = (2 * base - cur + mod) % mod;
			nxt = (nxt + 1) % mod;
			insert(sol[i + 1], cur, nxt);
			insert(sol[i], nxt, cur = (2 * base - nxt + mod) % mod);
		}
		insert(sol[i + 1], cur, 2 * N - 1);
	}
	for(j = 0;j < 2 * N;j += 1)
	{
		for(k = j + 1;k < 2 * N;k += 1)
		{
			if(!use[j][k])
				insert(sol[i], j, k);
		}
	}
}

int main()
{
	freopen("factor.in", "r", stdin);
	freopen("factor.out", "w", stdout);
	int i, j, k, cur, x;
	scanf("%d", &N);
	tot = 2 * N;
	mod = tot - 1;
	construct();
	scanf("%d", &M);
	for(i = cur = 0;i < M;i += 1)
	{
		scanf("%d", &x);
		for(j = 0;j < x;j += 1)
		{
			for(k = 1;k <= N;k += 1)
				printf("%d %d\n", sol[cur + j][k][0], sol[cur + j][k][1]);
		}
		cur += j;
		if(i + 1 < M)
			printf("\n");
	}
	exit(0);
}
