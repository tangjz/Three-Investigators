#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

const int ALPHA = 26;
const int NMAX = 25, MMAX = 10;
const int SMAX = 10 * MMAX;

struct State
{
	int mask;
	State *fail;
	State *trans[ALPHA];
};

int N, M;
long long f[NMAX + 1][SMAX][1<<MMAX], ans;
int pid;
State pool[SMAX];
char tmp[20];
vector<string> res;

State *insert(State *cur, char c)
{
	if(!cur->trans[c - 'a'])
		cur->trans[c - 'a'] = &pool[++pid];
	return cur->trans[c - 'a'];
}

void buildACAutomaton()
{
	int i;
	deque<State *> Q;
	State *cur;
	pool[0].fail = &pool[0];
	for(i = 0;i < ALPHA;i += 1)
	{
		if(!pool[0].trans[i])
			pool[0].trans[i] = &pool[0];
		else
		{
			pool[0].trans[i]->fail = &pool[0];
			Q.push_back(pool[0].trans[i]);
		}
	}
	while(!Q.empty())
	{
		cur = Q.front();
		Q.pop_front();
		for(i = 0;i < ALPHA;i += 1)
		{
			if(!cur->trans[i])
				cur->trans[i] = cur->fail->trans[i];
			else
			{
				cur->trans[i]->fail = cur->fail->trans[i];
				Q.push_back(cur->trans[i]);
			}
			cur->mask |= cur->fail->mask;
		}
	}
}

void solve()
{
	int i, j, k, l;
	State *nextState;
	f[0][0][0] = 1;
	for(i = 0;i < N;i += 1)
	{
		for(j = 0;j <= pid;j += 1)
		{
			for(k = 0;k < (1<<M);k += 1)
			{
				if(!f[i][j][k])
					continue;
				for(l = 0;l < ALPHA;l += 1)
				{
					nextState = pool[j].trans[l];
					f[i + 1][nextState - pool][k | nextState->mask] += f[i][j][k];
				}
			}
		}
	}
	for(i = 0;i <= pid;i += 1)
		ans += f[N][i][(1<<M) - 1];
}

void gen(int l, int s, int mask)
{
	int i, j, k;
	State *nextState;
	if(!l)
	{
		res.push_back(tmp);
		return;
	}
	for(i = 0;i <= pid;i += 1)
	{
		for(j = 0;j < (1<<M);j += 1)
		{
			if(!f[l - 1][i][j])
				continue;
			for(k = 0;k < ALPHA;k += 1)
			{
				nextState = pool[i].trans[k];
				if(nextState - pool == s && (j | nextState->mask) == mask)
				{
					tmp[l - 1] = k + 'a';
					gen(l - 1, i, j);
				}
			}
		}
	}

}

int main()
{
	int t;
	int i, j;
	char buf[20];
	State *cur;
	for(t = 1;;t += 1)
	{
		ans = pid = 0;
		memset(pool, 0, sizeof(pool));
		memset(f, 0, sizeof(f));
		memset(tmp, 0, sizeof(tmp));
		scanf("%d %d", &N, &M);
		if(!N && !M)
			break;
		for(i = 0;i < M;i += 1)
		{
			cur = &pool[0];
			scanf("%s", buf);
			for(j = 0;buf[j];j += 1)
				cur = insert(cur, buf[j]);
			cur->mask |= 1<<i;
		}
		buildACAutomaton();
		/*
		for(i = 0;i <= pid;i += 1)
		{
			printf("%d(mask:%d):", i, pool[i].mask);
			for(j = 0;j < ALPHA;j += 1)
				printf("(%c)%d ", 'a' + j, pool[i].trans[j] - pool);
			printf("\n");
		}
		*/
		solve();
		printf("Case %d: %lld suspects\n", t, ans);
		if(ans <= 42)
		{
			res.erase(res.begin(), res.end());
			for(i = 0;i < SMAX;i += 1)
			{
				if(f[N][i][(1<<M) - 1])
					gen(N, i, (1<<M) - 1);
			}
			sort(res.begin(), res.end());
			for(i = 0;i < res.size();i += 1)
				printf("%s\n", res[i].c_str());
		}
	}
	exit(0);
}
