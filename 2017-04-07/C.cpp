#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 100100;

int N, K, R, ans;
int camera[NMAX];

int main()
{
	int i, x, c;
	scanf("%d %d %d", &N, &K, &R);
	for(i = 0;i < K;i += 1)
	{
		scanf("%d", &x);
		camera[x] = 1;
	}
	for(i = 1, c = 0;i <= N;i += 1)
	{
		if(i > R)
			c -= camera[i - R];
		c += camera[i];
		if(i >= R && c < 2)
		{
			if(camera[i] != 1)
			{
				camera[i] = 1;
				c += 1;
				ans += 1;
			}
			if(i == R && c < 2)
			{
				camera[i - 1] = 1;
				c += 1;
				ans += 1;
			}
		}
	}
	printf("%d\n", ans);
	exit(0);
}
