#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 11000, MMAX = 510000;

struct Edge
{
	int x;
	int y;
	int c;
};

int N, M, P;
long long suf[MMAX];
Edge E[MMAX];

bool cmp(const Edge &x, const Edge &y)
{
	return x.c < y.c;
} 

int fa[NMAX];

int find(int x)
{
	int pa, tmp;
	for(pa = x;fa[pa] >= 0;pa = fa[pa]);
	while(x != pa)
	{
		tmp = fa[x];
		fa[x] = pa;
		x = tmp;
	}
	return pa;
}

long long Union(int x, int y)
{
	int X = find(x), Y = find(y);
	long long ans = 0;
	if(X == Y)
		return 0;
	if(fa[X] > fa[Y])
		swap(X, Y);
	ans = (long long)fa[X] * fa[Y] * 2;
	fa[X] += fa[Y];
	fa[Y] = X;
	return ans;
}

int main()
{
	int i, x;
	while(scanf("%d %d", &N, &M) != EOF)
	{
		memset(fa, -1, sizeof(fa));
		memset(suf, 0, sizeof(suf));
		for(i = 1;i <= M;i += 1)
			scanf("%d %d %d", &E[i].x, &E[i].y, &E[i].c);
		sort(E + 1, E + M + 1, cmp);
		for(i = 1;i <= M;i += 1)
			suf[i] = Union(E[i].x, E[i].y);
		for(i = M;i;i -= 1)
			suf[i] += suf[i + 1];
		scanf("%d", &P);
		for(i = 0;i < P;i += 1)
		{
			scanf("%d", &x);
			printf("%lld\n", suf[lower_bound(E + 1, E + M + 1, (Edge){0, 0, x}, cmp) - E]);
		}
	}
	exit(0);
}
