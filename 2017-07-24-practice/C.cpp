#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <bitset>

using namespace std;

const int ALPHA = 10;
const int NMAX = 1100, LMAX = 5001000;

int N;
char str[LMAX];
bitset<NMAX> mask[ALPHA], cur;

int main()
{
	int i, j, x, cnt;
	char tmp;
	while(scanf("%d", &N) != EOF)
	{
		cur.reset();
		for(i = 0;i < N;i += 1)
			mask[i].reset();
		for(i = 0;i < N;i += 1)
		{
			scanf("%d", &cnt);
			for(j = 0;j < cnt;j += 1)
			{
				scanf("%d", &x);
				mask[x].set(i);
			}
		}
		scanf("%s", str);
		for(i = 0;str[i];i += 1)
		{
			cur = ((cur<<1).set(0)) & mask[str[i] - '0'];
			if(cur.test(N - 1))
			{
				tmp = str[i + 1];
				str[i + 1] = '\0';
				printf("%s\n", str + i - N + 1);
				str[i + 1] = tmp;
			}
		}
	}
	exit(0);
}
