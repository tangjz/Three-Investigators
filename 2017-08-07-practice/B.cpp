#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 310, INF = ~0u>>1;

int T;
int N, M;
int cnt[2], id[NMAX];
int type[NMAX], level[NMAX], ATK[NMAX];
int match[NMAX], slack[NMAX], pre[NMAX];
int label[2][NMAX], weight[NMAX][NMAX];
bool visit[NMAX];

void augment(int root, int n)
{
	int x, y, delta, nxt, last;
	memset(visit, 0, sizeof(visit));
	fill(slack, slack + NMAX, INF);
	match[last = 0] = root;
	do{
		visit[last] = true;
		x = match[last];
		delta = INF;
		for(y = 1;y <= n;y += 1)
		{
			if(visit[y])
				continue;
			if(label[0][x] + label[1][y] - weight[x][y] < slack[y])
			{
				slack[y] = label[0][x] + label[1][y] - weight[x][y];
				pre[y] = last;
			}
			if(slack[y] < delta)
			{
				delta = slack[y];
				nxt = y;
			}
		}
		for(y = 0;y <= n;y += 1)
		{
			if(visit[y])
			{
				label[0][match[y]] -= delta;
				label[1][y] += delta;
			}
			else
				slack[y] -= delta;
		}
		last = nxt;
	}while(match[last]);
	for(y = last;y;y = pre[y])
		match[y] = match[pre[y]];
}

int KM(int n)
{
	int i, j, delta;
	int res = 0;
	for(i = 1;i <= n;i += 1)
	{
		delta = 0;
		for(j = 1;j <= n;j += 1)
			delta = max(delta, weight[i][j]);
		label[0][i] = delta;
		label[1][i] = 0;
		match[i] = 0;
	}
	for(i = 1;i <= n;i += 1)
		augment(i, n);
	for(i = 1;i <= n;i += 1)
		res += label[0][i] + label[1][i];
	return res;
}

int main()
{
	int t;
	int i, j, k, l, atk, r[3];
	int tot;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		tot = 0;
		memset(weight, 0, sizeof(weight));
		memset(cnt, 0, sizeof(cnt));
		scanf("%d %d", &N, &M);
		for(i = 1;i <= N;i += 1)
		{
			scanf("%d %d %d", &type[i], &level[i], &ATK[i]);
			tot += ATK[i];
			id[i] = ++cnt[type[i]];
		}
		for(i = 1;i <= M;i += 1)
		{
			scanf("%d %d %d", &l, &atk, &r[0]);
			for(j = 1;j <= r[0];j += 1)
				scanf("%d", &r[j]);
			for(j = 1;j <= N;j += 1)
			{
				if(r[0] && j != r[1])
					continue;
				for(k = 1;k <= N;k += 1)
				{
					if(r[0] >= 2 && k != r[2])
						continue;
					if(type[j] == type[k]
						|| level[j] + level[k] != l)
						continue;
					if(!type[j])
						weight[id[j]][id[k]] = max(weight[id[j]][id[k]], atk - (ATK[j] + ATK[k]));
					else
						weight[id[k]][id[j]] = max(weight[id[k]][id[j]], atk - (ATK[j] + ATK[k]));
				}
			}
		}
		printf("%d\n", tot + KM(max(cnt[0], cnt[1])));
	}
	exit(0);
}
