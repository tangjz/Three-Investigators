#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 210000;

int N, M;
int fa[NMAX], cnt[NMAX];
long long sum[NMAX];

int Find(int x)
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

void Union(int x, int y)
{
	int X = Find(x), Y = Find(y);
	if(X == Y)
		return;
	if(fa[X] > fa[Y])
		swap(X, Y);
	fa[X] += fa[Y];
	fa[Y] = X;
	cnt[X] += cnt[Y];
	sum[X] += sum[Y];
}

int main()
{
	int i, opt, x, y, X, Y;
	while(scanf("%d %d", &N, &M) != EOF)
	{
		for(i = 1;i <= N;i += 1)
		{
			fa[i + N] = -2;
			fa[i] = i + N;
			cnt[i + N] = 1;
			sum[i + N] = i;
		}
		for(i = 0;i < M;i += 1)
		{
			scanf("%d", &opt);
			if(opt == 1)
			{
				scanf("%d %d", &x, &y);
				Union(x, y);
			}
			else if(opt == 2)
			{
				scanf("%d %d", &x, &y);
				X = Find(x);
				Y = Find(y);
				if(X != Y)
				{
					fa[x] = Y;
					cnt[X] -= 1;
					cnt[Y] += 1;
					sum[X] -= x;
					sum[Y] += x;
				}
			}
			else
			{
				scanf("%d", &x);
				X = Find(x);
				printf("%d %lld\n", cnt[X], sum[X]);
			}
		}
	}
	exit(0);
}
