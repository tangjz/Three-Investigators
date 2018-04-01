#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 2100000, maxm = 4300000;
long long INF = 10000000000000000ll;
int n, m, a, b, N, M, S, T, lnk[maxn], level[maxn], que[maxn], L, R;
struct Edge
{
	int nxt, v;
	long long f;
} e[maxm << 1];
void addEdge(int u, int v, int c)
{
	e[M] = (Edge){lnk[u], v, c};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0};
	lnk[v] = M++;
}
bool bfs()
{
	L = R = 0;
	memset(level, 0, N * sizeof(int));
	level[S] = 1;
	que[R++] = S;
	while(L < R)
	{
		int u = que[L++];
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			if(e[it].f && !level[e[it].v])
			{
				level[e[it].v] = level[u] + 1;
				que[R++] = e[it].v;
			}
	}
	return level[T];
}
long long dfs(int u, long long lim)
{
	if(u == T || !lim)
		return lim;
	long long ret = 0;
	for(int it = lnk[u], tmp; it != -1; it = e[it].nxt)
		if(e[it].f && level[e[it].v] == level[u] + 1
		&& (tmp = dfs(e[it].v, std::min(e[it].f, lim - ret))))
		{
			e[it].f -= tmp;
			e[it ^ 1].f += tmp;
			ret += tmp;
		}
	if(!ret)
		level[u] = 0;
	return ret;
}

int coor2id(int x, int y)
{
	return x * m + y;
}

int main()
{
	int i, j;
	char c;
	scanf("%d %d %d %d", &n, &m, &a, &b);
	N = n * m + 2;
	M = 0;
	S = N - 2;
	T = N - 1;
	memset(lnk, -1, N * sizeof(int));
	for(i = 0;i < n;i += 1)
	{
		for(j = 0;j < m;j += 1)
		{
			if(i + 1 < n)
			{
				addEdge(coor2id(i, j), coor2id(i + 1, j), a);
				addEdge(coor2id(i + 1, j), coor2id(i, j), a);
			}
			if(j + 1 < m)
			{
				addEdge(coor2id(i, j), coor2id(i, j + 1), a);
				addEdge(coor2id(i, j + 1), coor2id(i, j), a);
			}
			scanf(" %c", &c);
			if(c == '#')
				addEdge(S, coor2id(i, j), b);
			else
				addEdge(coor2id(i, j), T, b);
		}
	}
	long long flow = 0;
	while(bfs())
		for(long long tmp; (tmp = dfs(S, INF)); flow += tmp);
	printf("%lld\n", flow);
	return 0;
}
