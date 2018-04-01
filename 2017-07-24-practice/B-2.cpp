#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 110000, VMAX = 220000, EMAX = 220000;

struct Edge
{
	int y;
	int next;
};

int T, N;
int pali[2 * NMAX], Rank[NMAX], perm[NMAX];
int father[NMAX], repMinRank[NMAX], repMaxRank[NMAX];
char ans[NMAX], minimum[NMAX];
bool great[NMAX];
vector<pair<int, int> > unequal;
int eid, V[VMAX];
Edge E[EMAX];

inline void scan(int &x)
{
    register int ch;
    while((ch = getchar()) < '0' || ch > '9');
    for(x = ch - '0'; (ch = getchar()) >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch - '0'));
}

int Find(int x)
{
	int pa, tmp;
	for(pa = x;father[pa] >= 0;pa = father[pa]);
	while(x != pa)
	{
		tmp = father[x];
		father[x] = pa;
		x = tmp;
	}
	return pa;
}

void Union(int x, int y)
{
	int X = Find(x), Y = Find(y);
	if(X == Y)
		return;
	if(father[X] > father[Y])
		swap(X, Y);
	father[X] += father[Y];
	father[Y] = X;
	repMinRank[X] = min(repMinRank[X], repMinRank[Y]);
	repMaxRank[X] = max(repMaxRank[X], repMaxRank[Y]);
}

void insert(int x, int y)
{
	E[++eid] = (Edge){y, V[x]};
	V[x] = eid;
}

bool manacher()
{
	int i, j;
	int pos = 0, reflect, maxRight = 1;
	for(i = 1;i < 2 * N;i += 1)
	{
		if(i >= maxRight)
		{
			if(pali[i] > min(i, 2 * N - i) + 1)
				return false;
			for(j = 1;j < pali[i];j += 1)
			{
				if((i + j) & 1)
					Union((i + j)>>1, (i - j)>>1);
			}
			if(i + pali[i] <= 2 * N && i - pali[i] >= 0)
			{
				if((i + pali[i]) & 1)
					unequal.push_back(make_pair((i + pali[i])>>1, (i - pali[i])>>1));
				else
					return false;
			}
			pos = i;
			maxRight = i + pali[i];
		}
		else
		{
			reflect = 2 * pos - i;
			if(pali[reflect] < maxRight - i)
			{
				if(pali[i] != pali[reflect])
					return false;
			}
			else
			{
				if(pali[i] < maxRight - i || pali[i] > min(i, 2 * N - i) + 1)
					return false;
				for(j = maxRight - i;j < pali[i];j += 1)
				{
					if((i + j) & 1)
						Union((i + j)>>1, (i - j)>>1);
				}
				if(i + pali[i] <= 2 * N && i - pali[i] >= 0)
				{
					if((i + pali[i]) & 1)
						unequal.push_back(make_pair((i + pali[i])>>1, (i - pali[i])>>1));
					else
						return false;
				}
				if(i + pali[i] > maxRight)
				{
					maxRight = i + pali[i];
					pos = i;
				}
			}
		}
	}
	return true;
}

bool generate()
{
	int i, r, cur, p, x, y;
	char c;
	for(i = 0;i + 1 < N;i += 1)
	{
		if(Rank[perm[i] + 1] > Rank[perm[i + 1] + 1])
			great[i] = true;
	}
	for(i = r = 0;i < N;i += 1)
	{
		p = perm[i];
		r = max(r, repMaxRank[Find(p)]);
		if(i + 1 <= r)
			Union(p, perm[i + 1]);
	}
	for(i = 0;i < unequal.size();i += 1)
	{
		x = repMinRank[Find(unequal[i].first)];
		y = repMinRank[Find(unequal[i].second)];
		if(x > y)
			swap(x, y);
		if(x == y)
			return false;
		insert(perm[x], perm[y]);
	}
	for(i = cur = 0, c = 'a';i < N;i += 1)
	{
		p = perm[i];
		ans[p] = max(c, minimum[p]);
		if(ans[p] > 'z')
			return false;
		if(perm[repMinRank[Find(p)]] != p)
		{
			if(ans[perm[repMinRank[Find(p)]]] < ans[p])
				return false;
			else
				ans[p] = ans[perm[repMinRank[Find(p)]]];
		}
		c = ans[p];
		for(cur = V[p];cur;cur = E[cur].next)
			minimum[E[cur].y] = max(minimum[E[cur].y], (char)(ans[p] + 1));
		if(great[i])
			c += 1;
	}
	for(i = 0;i < N;i += 1)
	{
		if(ans[i] != ans[Find(i)])
			return false;
	}
	return true;
}

int main()
{
	int t, i, x;
	bool flag;
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		//scanf("%d", &N);
		scan(N);
		eid = 0;
		memset(great, 0, sizeof(bool) * (N + 10));
		memset(minimum, 0, sizeof(char) * (N + 10));
		memset(ans, 0, sizeof(char) * (N + 10));
		memset(father, -1, sizeof(int) * (N + 10));
		unequal.erase(unequal.begin(), unequal.end());
		memset(V, 0, sizeof(int) * (N + 10));
		for(i = 0;i < N;i += 1)
		{
			//scanf("%d", &x);
			scan(x);
			perm[i] = x;
			repMinRank[x] = repMaxRank[x] = Rank[x] = i;
		}
		Rank[N] = -1;
		pali[0] = 1;
		for(i = 1;i < 2 * N;i += 1)
		{
			//scanf("%d", &pali[i]);
			scan(pali[i]);
			pali[i] += 1;
		}
		pali[2 * N] = 1;
		flag = manacher();
		flag = flag && generate();
		printf("Case #%d: ", t);
		if(flag)
			printf("%s\n", ans);
		else
			printf("Wrong calculation!\n");
	}
	exit(0);
}
