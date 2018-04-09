#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 6;

int N = 4;
long double A[NMAX][NMAX], ans;

int main()
{
	int i, j, cur, nxt;
	char c;
	bool init;
	for(i = 1;i <= 4;i += 1)
	{
		for(j = 1;j <= 4;j += 1)
			scanf("%Lf", &A[i][j]);
	}
	ans = 1.0;
	init = true;
	while(1)
	{
		scanf("%d%c", &nxt, &c);
		//printf("ans: %.9Lf\n", ans);
		if(!init)
			ans = ans * A[cur][nxt];
		else
			init = false;
		cur = nxt;
		if(c == '\n')
			break;
	}
	printf("%.9Lf\n", ans);
	ans = 1.0;
	init = true;
	while(1)
	{
		scanf("%d%c", &nxt, &c);
		if(!init)
			ans = ans * A[cur][nxt];
		else
			init = false;
		cur = nxt;
		if(c == '\n')
			break;
	}
	printf("%.9Lf\n", ans);
	scanf("%d", &cur);
	printf("%.9Lf\n", 1.0 / (1 - A[cur][cur]));
	scanf("%d", &cur);
	printf("%.9Lf\n", 1.0 / (1 - A[cur][cur]));
	exit(0);
}
