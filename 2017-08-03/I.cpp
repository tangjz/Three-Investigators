#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

int T;
int N, cnt[2];

int main()
{
	int t, i, x;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		cnt[0] = cnt[1] = 0;
		scanf("%d", &N);
		for(i = 0;i < N;i += 1)
		{
			scanf("%d", &x);
			cnt[x & 1] += 1;
		}
		printf("2 %d\n", cnt[0] >= cnt[1]?0:1);
	}
	exit(0);
}
