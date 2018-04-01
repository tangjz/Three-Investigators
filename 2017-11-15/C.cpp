#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 210;
const int EMAX = 2100;
const double eps = 1e-10, INF = 1e20;

struct Edge
{
	int y;
	double w;
	int next;
};

int N, M, Q;
int Z[NMAX], X[NMAX], Y[NMAX];
int V[NMAX], eid;
bool visit[NMAX];
double d[NMAX][NMAX];
int fa[NMAX][NMAX];
Edge E[EMAX];
priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > que;

void insert(int x, int y, double w)
{
	E[++eid] = (Edge){y, w, V[x]};
	V[x] = eid;
}

inline int sqr(int x)
{
	return x * x;
}

double dist(int u, int v)
{
	return sqrt(25 * sqr(Z[u] - Z[v]) + sqr(X[u] - X[v]) + sqr(Y[u] - Y[v]));
}

void dijkstra(int s)
{
	int i, e, x;
	double dist;
	memset(visit, 0, sizeof(visit));
	for(i = 0;i < N;i += 1)
		d[s][i] = INF;
	d[s][s] = 0.0;
	que.push(make_pair(0.0, s));
	while(!que.empty())
	{
		x = que.top().second;
		dist = que.top().first;
		que.pop();
		if(fabs(dist - d[s][x]) < eps)
		{
			visit[x] = true;
			for(e = V[x];e;e = E[e].next)
			{
				if(!visit[E[e].y] && d[s][x] + E[e].w < d[s][E[e].y] - eps)
				{
					d[s][E[e].y] = d[s][x] + E[e].w;
					fa[s][E[e].y] = x;
					que.push(make_pair(d[s][E[e].y], E[e].y));
				}
			}
		}
	}
}

void construct(int s, int x, bool last)
{
	if(s != x)
		construct(s, fa[s][x], false);
	printf("%d%c", x, " \n"[last?1:0]);
}

int main()
{
	int i, x, y;
	double w;
	char buff[20];
	scanf("%d %d", &N, &M);
	for(i = 0;i < N;i += 1)
		scanf("%d %d %d", &Z[i], &X[i], &Y[i]);
	for(i = 0;i < M;i += 1)
	{
		scanf("%d %d %s", &x, &y, buff);
		if(buff[0] == 'w' || buff[0] == 's')
		{
			w = dist(x, y);
			insert(x, y, w);
			insert(y, x, w);
		}
		else if(buff[0] == 'l')
		{
			insert(x, y, 1.0);
			insert(y, x, 1.0);
		}
		else
		{
			insert(x, y, 1.0);
			insert(y, x, 3.0 * dist(x, y));
		}
	}
	for(i = 0;i < N;i += 1)
		dijkstra(i);
	scanf("%d", &Q);
	for(i = 0;i < Q;i += 1)
	{
		scanf("%d %d", &x, &y);
		construct(x, y, true);
	}
	exit(0);
}
