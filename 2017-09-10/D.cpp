#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 110000;

int T, N, K;
int number[NMAX], f[NMAX];

bool cmp1(int x, int y)
{
	return x < y;
}

bool cmp2(int x, int y)
{
	if(!x)
		return true;
	if(!y)
		return false;
	return x > y;
}

int solve(bool (*cmp)(int, int))
{
	int i, x, pos = 0;
	memset(f, 0, sizeof(f));
	for(i = 1;i <= N;i += 1)
	{
		x = upper_bound(f, f + pos + 1, number[i], cmp) - f;
		if(x > pos)
			pos += 1;
		if(!f[x] || cmp(number[i], f[x]))
			f[x] = number[i];
	}
	return pos;
}

int main()
{
	int t, i, res;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		scanf("%d %d", &N, &K);
		for(i = 1;i <= N;i += 1)
			scanf("%d", &number[i]);
		res = solve(cmp1);
		res = max(res, solve(cmp2));
		if(res >= N - K)
			printf("A is a magic array.\n");
		else
			printf("A is not a magic array.\n");
	}
	exit(0);
}
