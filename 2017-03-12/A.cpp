#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <bitset>

using namespace std;

const int NMAX = 5100, EMAX = 21000;

struct Edge
{
	int y;
	int next;
};

int A, B, E, P, ansA, ansB, ansImp;
int V[NMAX], eid, indeg[NMAX];
Edge Ed[EMAX];
deque<int> Q;
bitset<NMAX> prec[NMAX];

void insert(int x, int y)
{
	Ed[++eid] = (Edge){y, V[x]};
	V[x] = eid;
	indeg[y] += 1;
}

int main()
{
	int i, j, x, y, cnt;
	scanf("%d %d %d %d", &A, &B, &E, &P);
	for(i = 1;i <= P;i += 1)
	{
		scanf("%d %d", &x, &y);
		insert(x, y);
	}
	for(i = 0;i < E;i += 1)
	{
		prec[i].reset();
		prec[i].set(i);
		if(!indeg[i])
			Q.push_back(i);
	}
	while(!Q.empty())
	{
		x = Q.front();
		Q.pop_front();
		for(i = V[x];i;i = Ed[i].next)
		{
			y = Ed[i].y;
			indeg[y] -= 1;
			prec[y] |= prec[x];
			if(!indeg[y])
				Q.push_back(y);
		}
	}
	for(i = 0;i < E;i += 1)
	{
		for(j = cnt = 0;j < E;j += 1)
		{
			if(!prec[j].test(i))
				cnt += 1;
		}
		cnt += 1;
		if(cnt <= A)
			ansA += 1;
		if(cnt <= B)
			ansB += 1;
		if((int)prec[i].count() > B)
			ansImp += 1;
	}
	printf("%d\n%d\n%d\n", ansA, ansB, ansImp);
	exit(0);
}
