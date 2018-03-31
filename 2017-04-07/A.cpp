#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 60;

int N, f[NMAX], ans;
char str[NMAX];

int main()
{
	int i, j;
	scanf("%s", str);
	N = strlen(str);
	for(i = 0;i < N;i += 1)
	{
		f[i] = 1;
		for(j = 0;j < N;j += 1)
		{
			if(str[j] < str[i])
				f[i] = max(f[i], f[j] + 1);
		}
		ans = max(ans, f[i]);
	}
	printf("%d\n", 26 - ans);
	exit(0);
}
