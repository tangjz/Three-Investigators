#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 510000, PMAX = 1100000;

struct Node
{
	int p;
	int pre;
};

int N, M, C = 1;
int pid;
Node pool[PMAX];
int cur[NMAX], del[NMAX];

void insert(int stack[], int c, int p)
{
	pool[++pid] = (Node){p, stack[c]};
	stack[c] = pid;
}

int main()
{
	int i, c, p;
	char opt[50];
	scanf("%d %d", &N, &M);
	for(i = 0;i < N;i += 1)
	{
		scanf("%s %d", opt, &c);
		if(!strcmp(opt, "learn"))
		{
			scanf("%d", &p);
			insert(cur, c, p);
			del[c] = 0;
		}
		else if(!strcmp(opt, "rollback"))
		{
			insert(del, c, pool[cur[c]].p);
			cur[c] = pool[cur[c]].pre;
		}
		else if(!strcmp(opt, "relearn"))
		{
			insert(cur, c, pool[del[c]].p);
			del[c] = pool[del[c]].pre;
		}
		else if(!strcmp(opt, "clone"))
		{
			C += 1;
			cur[C] = cur[c];
			del[C] = del[c];
		}
		else
		{
			if(!cur[c])
				printf("basic\n");
			else
				printf("%d\n", pool[cur[c]].p);
		}
	}
	exit(0);
}
