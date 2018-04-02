#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int base = 50;
int N, M;
vector<pair<int, int> > E;

int main()
{
	int i, j, k;
	for(i = 1;i <= base;i += 1)
		E.push_back(make_pair(i, i + base));
	N = 2 * base;
	for(i = base;i >= 2;i -= 1)
	{
		for(j = 1;i * j <= base;j += 1)
		{
			N += 1;
			for(k = (j - 1) * i + 1;k <= i * j;k += 1)
				E.push_back(make_pair(N, k));
		}
	}
	M = E.size();
	printf("%d %d\n", N, M);
	for(i = 0;i < M;i += 1)
		printf("%d %d\n", E[i].first, E[i].second);
	printf("%d\n", base);
	for(i = 1;i <= base;i += 1)
		printf("%d\n", i);
	exit(0);
}
