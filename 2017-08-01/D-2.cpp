#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int LMAX = 30;
const int NMAX = 510000, NODE_MAX = NMAX * LMAX;

struct Node
{
	int size[2];
	Node *ch[2];
};

int T;
int N, A[NMAX];
long long sum[LMAX][2], ans;

int pid;
Node pool[NODE_MAX], *null = &pool[0], *root;

Node *create()
{
	pool[++pid] = *null;
	return &pool[pid];
}

long long insert(int x, int side, int delta)
{
	int i;
	long long res = 0;
	Node *cur = root;
	for(i = LMAX - 1;i >= 0;i -= 1)
	{
		sum[i][0] -= (long long)cur->ch[0]->size[0] * cur->ch[1]->size[1];
		sum[i][1] -= (long long)cur->ch[1]->size[0] * cur->ch[0]->size[1];
		cur->size[side] += delta;
		if(cur->ch[(x>>i) & 1] == null)
			cur->ch[(x>>i) & 1] = create();
		cur = cur->ch[(x>>i) & 1];
	}
	cur->size[side] += delta;
	cur = root;
	for(i = LMAX - 1;i >= 0;i -= 1)
	{
		sum[i][0] += (long long)cur->ch[0]->size[0] * cur->ch[1]->size[1];
		sum[i][1] += (long long)cur->ch[1]->size[0] * cur->ch[0]->size[1];
		res += sum[i][(x>>i) & 1];
		cur = cur->ch[(x>>i) & 1];
	}
	return res;
}

int main()
{
	int t, i;
	null->ch[0] = null->ch[1] = null;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		pid = ans = 0;
		root = create();
		memset(sum, 0, sizeof(sum));
		scanf("%d", &N);
		for(i = 0;i < N;i += 1)
		{
			scanf("%d", &A[i]);
			insert(A[i], 1, 1);
		}
		for(i = 0;i < N;i += 1)
		{
			ans += insert(A[i], 1, -1);
			insert(A[i], 0, 1);
		}
		printf("%lld\n", ans);
	}
	exit(0);
}
