#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 110;

int N;
int fa[NMAX], value[NMAX];
bool mat[NMAX][NMAX];

int find(int x)
{
	int pa, tmp, v = 0;
	for(pa = x;fa[pa] >= 0;pa = fa[pa])
		v ^= value[pa];
	//printf("%d's pa:%d\n", x, pa);
	while(x != pa)
	{
		tmp = fa[x];
		fa[x] = pa;
		value[x] = (v ^= value[x]);
		x = tmp;
	}
	return pa;
}

bool Union(int x, int y, int v)
{
	int X = find(x), Y = find(y);
	v ^= value[x] ^ value[y];
	//printf("X:%d, v:%d, Y:%d, v:%d | v:%d\n", X, value[x], Y, value[y], v);
	if(X == Y)
		return !v;
	if(fa[X] > fa[Y])
		swap(X, Y);
	fa[X] += fa[Y];
	fa[Y] = X;
	value[Y] = v;
	return true;
}

int main()
{
	int i, j, x;
	while(scanf("%d", &N) != EOF)
	{
		memset(mat, 0, sizeof(mat));
		memset(fa, -1, sizeof(fa));
		for(i = 1;i <= N;i += 1)
		{
			while(1)
			{
				scanf("%d", &x);
				if(!x)
					break;
				mat[i][x] = true;
			}
		}
		for(i = 1;i <= N;i += 1)
		{
			for(j = 1;j < i;j += 1)
			{
				if(!mat[i][j] || !mat[j][i])
				{
					//printf("Union %d, %d with 1\n", i, j);
					if(!Union(i, j, 1))
						break;
				}
			}
			if(j < i)
				break;
		}
		printf("%s\n", i > N?"YES":"NO");
	}
	exit(0);
}
