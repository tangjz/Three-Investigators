#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MMAX = 110000;
const int VMAX = 110000, EMAX = 210000;

struct Edge
{
	int id;
	int y;
	int next;
};

int T;
int N, M;
int ans[MMAX];

int V[VMAX], eid;
Edge E[EMAX];

int stamp;
int maxID[VMAX], DFN[VMAX], LOW[VMAX];

void insert(int x, int y, int id)
{
	E[++eid] = (Edge){id, y, V[x]};
	V[x] = eid;
}

void tarjan(int x, int paEID)
{
	int e, y;
	maxID[x] = x;
	DFN[x] = LOW[x] = ++stamp;
	for(e = V[x];e;e = E[e].next)
	{
		if(E[e].id == paEID)
			continue;
		y = E[e].y;
		if(!DFN[y])
		{
			tarjan(y, E[e].id);
			LOW[x] = min(LOW[x], LOW[y]);
			maxID[x] = max(maxID[x], maxID[y]);
		}
		else
			LOW[x] = min(LOW[x], DFN[y]);
	}
	if(DFN[x] == LOW[x] && paEID)
		ans[paEID] = maxID[x];
}

int main()
{
	int t;
	int i, x, y;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		stamp = eid = 0;
		memset(V, 0, sizeof(V));
		memset(DFN, 0, sizeof(DFN));
		memset(ans, 0, sizeof(ans));
		scanf("%d %d", &N, &M);
		for(i = 1;i <= M;i += 1)
		{
			scanf("%d %d", &x, &y);
			insert(x, y, i);
			insert(y, x, i);
		}
		tarjan(N, 0);
		for(i = 1;i <= M;i += 1)
		{
			if(ans[i])
				printf("%d %d\n", ans[i], ans[i] + 1);
			else
				printf("0 0\n");
		}
	}
	exit(0);
}
