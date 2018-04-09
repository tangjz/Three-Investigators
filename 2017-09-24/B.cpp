#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int SMAX = 110;

int N, ans;
int seat[SMAX];

int main()
{
	int i, s, t, k;
	while(1)
	{
		ans = 0;
		memset(seat, 0, sizeof(seat));
		scanf("%d", &N);
		for(i = 1;i <= N;i += 1)
		{
			scanf("%d %d %d", &s, &t, &k);
			seat[s] += k;
			seat[t] -= k;
		}
		for(i = 1;i <= 100;i += 1)
		{
			seat[i] += seat[i - 1];
			ans = max(ans, seat[i]);
		}
		if(!N)
		{
			printf("*\n");
			break;
		}
		else
			printf("%d\n", ans);
	}
	exit(0);
}
