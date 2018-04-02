#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int ALPHA = 2, MOD = 998244353;
const int NMAX = 10, NODEMAX = 130, MASKMAX = 1<<6;

struct Node
{
	Node *fail;
	int mask;
	int len[NMAX];
	Node *next[ALPHA];
};

struct State
{
	int i;
	int mask;
	int j;
	int k;
};

int T;
int N, L;
int pid1, pid2, ans;
Node pool1[NODEMAX], pool2[NODEMAX], *root, *antiRoot;
deque<Node *> Q;
deque<State> S;
int f[2][MASKMAX][NODEMAX][NODEMAX];
int tag[MASKMAX][NODEMAX][NODEMAX];
int intern[NODEMAX][NODEMAX];

void insert(Node pool[], int &pid, Node *&cur, int c)
{
	if(!cur->next[c])
		cur->next[c] = &pool[pid++];
	cur = cur->next[c];
}

void buildACAutomaton(Node *r)
{
	int i;
	for(i = 0;i < 2;i += 1)
	{
		if(!r->next[i])
			r->next[i] = r;
		else
		{
			r->next[i]->fail = r;
			Q.push_back(r->next[i]);
		}
	}
	while(!Q.empty())
	{
		r = Q.front();
		Q.pop_front();
		r->mask |= r->fail->mask;
		for(i = 0;i < N;i += 1)
			r->len[i] |= r->fail->len[i];
		for(i = 0;i < 2;i += 1)
		{
			if(!r->next[i])
				r->next[i] = r->fail->next[i];
			else
			{
				r->next[i]->fail = r->fail->next[i];
				Q.push_back(r->next[i]);
			}
		}
	}
}

int main()
{
	int t, i, j, k, nmask, len;
	char buf[NMAX][30];
	Node *pos, *nj, *nk;
	State state;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		pid1 = pid2 = ans = 0;
		memset(pool1, 0, sizeof(pool1));
		memset(pool2, 0, sizeof(pool2));
		memset(f, 0, sizeof(f));
		memset(tag, 0, sizeof(tag));
		memset(intern, 0, sizeof(intern));
		root = &pool1[pid1++];
		antiRoot = &pool2[pid2++];
		scanf("%d %d", &N, &L);
		for(i = 0;i < N;i += 1)
		{
			scanf("%s", buf[i]);
			len = strlen(buf[i]);

			pos = root;
			for(j = 0;j < len;j += 1)
			{
				insert(pool1, pid1, pos, buf[i][j] - '0');
				pos->len[i] |= 1<<(j + 1);
			}
			pos->mask |= 1<<i;

			pos = antiRoot;
			for(j = len - 1;j >= 0;j -= 1)
			{
				insert(pool2, pid2, pos, buf[i][j] - '0');
				pos->len[i] |= 1<<j;
			}
			pos->mask |= 1<<i;
		}
		buildACAutomaton(root);
		buildACAutomaton(antiRoot);
		for(i = 0;i < pid1;i += 1)
		{
			for(j = 0;j < pid2;j += 1)
			{
				for(k = 0;k < N;k += 1)
				{
					if(pool1[i].len[k] & pool2[j].len[k])
						intern[i][j] |= 1<<k;
				}
			}
		}
		f[0][0][0][0] = 1;
		S.push_back((State){0, 0, 0, 0});
		while(!S.empty())
		{
			state = S.front();
			S.pop_front();
			//printf("len:%d, pos:%d, anti:%d, mask:%d, f:%d\n", state.i, state.j, state.k, state.mask, f[state.i & 1][state.mask][state.j][state.k]);
			if(state.i == L)
			{
				if((state.mask | intern[state.j][state.k]) == (1<<N) - 1)
					(ans += f[state.i & 1][state.mask][state.j][state.k]) %= MOD;
			}
			else
			{
				for(i = 0;i < 2;i += 1)
				{
					nj = (pool1 + state.j)->next[i];
					nk = (pool2 + state.k)->next[i ^ 1];
					nmask = state.mask | nj->mask | nk->mask;
					if(tag[nmask][nj - pool1][nk - pool2] != state.i + 1)
					{
						tag[nmask][nj - pool1][nk - pool2] = state.i + 1;
						f[(state.i + 1) & 1][nmask][nj - pool1][nk - pool2] = 0;
						S.push_back((State){state.i + 1, nmask, (int)(nj - pool1), (int)(nk - pool2)});
					}
					(f[(state.i + 1) & 1][nmask][nj - pool1][nk - pool2] += f[state.i & 1][state.mask][state.j][state.k]) %= MOD;
				}
			}
		}
		printf("%d\n", ans);
	}
	exit(0);
}
