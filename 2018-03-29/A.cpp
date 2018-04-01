#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

const int MOD = 1000000007, POW1 = 5003, POW2 = 5011;
const int DMAX = 210, NMAX = 5100;

int ans;
int D, N, M;
int fa[DMAX][NMAX], hashValue1[NMAX], hashValue2[NMAX];
int P1[DMAX], P2[DMAX];
vector<int> member[DMAX][NMAX];
unordered_map<long long, int> hashTable;

int find(int type, int x)
{
	int pa, tmp;
	for(pa = x;fa[type][pa] >= 0;pa = fa[type][pa]);
	while(x != pa)
	{
		tmp = fa[type][x];
		fa[type][x] = pa;
		x = tmp;
	}
	return pa;
}

void editHash(int cur, int type, int X, int Y)
{
	//printf("cur:%d, type:%d, X:%d, Y:%d\n", cur, type, X, Y);
	hashTable[((long long)hashValue1[cur]<<32) | hashValue2[cur]] -= 1;
	ans -= hashTable[((long long)hashValue1[cur]<<32) | hashValue2[cur]];
	if(hashTable[((long long)hashValue1[cur]<<32) | hashValue2[cur]] == 0)
		hashTable.erase(((long long)hashValue1[cur]<<32) | hashValue2[cur]);
	//printf("P[%d]: %d\n", type, P[type]);
	hashValue1[cur] = (hashValue1[cur] + (long long)(X - Y) * P1[type] % MOD + MOD) % MOD;
	hashValue2[cur] = (hashValue2[cur] + (long long)(X - Y) * P2[type] % MOD + MOD) % MOD;
	ans += hashTable[((long long)hashValue1[cur]<<32) | hashValue2[cur]];
	hashTable[((long long)hashValue1[cur]<<32) | hashValue2[cur]] += 1;
	//printf("after hashValue:%d\n", hashValue[cur]);
}

void Merge(int type, int X, int Y)
{
	int i, cur;
	for(i = 0;i < member[type][Y].size();i += 1)
	{
		cur = member[type][Y][i];
		editHash(cur, type, X, Y);
		member[type][X].push_back(cur);
	}
	member[type][Y].erase(member[type][Y].begin(), member[type][Y].end());
}

void Union(int type, int x, int y)
{
	int X = find(type, x), Y = find(type, y);
	if(X == Y)
		return;
	if(fa[type][X] > fa[type][Y])
		swap(X, Y);
	fa[type][X] += fa[type][Y];
	fa[type][Y] = X;
	Merge(type, X, Y);
}

int main()
{
	int i, j, x, y, t;
	memset(fa, -1, sizeof(fa));
	scanf("%d %d %d", &D, &N, &M);
	P1[0] = P2[0] = 1;
	for(i = 1;i <= D;i += 1)
	{
		P1[i] = (long long)P1[i - 1] * POW1 % MOD;
		P2[i] = (long long)P2[i - 1] * POW2 % MOD;
	}
	for(i = 1;i <= N;i += 1)
	{
		for(j = 1;j <= D;j += 1)
		{
			hashValue1[i] = (hashValue1[i] + (long long)P1[j] * i) % MOD;
			hashValue2[i] = (hashValue2[i] + (long long)P2[j] * i) % MOD;
			member[j][i].push_back(i);
		}
		hashTable[((long long)hashValue1[i]<<32) | hashValue2[i]] = 1;
	}
	for(i = 1;i <= M;i += 1)
	{
		scanf("%d %d %d", &x, &y, &t);
		Union(t, x, y);
		printf("%d\n", ans * 2 + N);
	}
	//system("pause");
	exit(0);
}
