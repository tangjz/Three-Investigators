#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 1100000;

int ans;
char str[NMAX];

int main()
{
	int i, val, len;
	scanf("%s", str);
	for(i = val = len = 0;str[i];i += 1)
	{
		switch(str[i])
		{
		case 'M':
			len += 1;
			break;
		case 'K':
			val -= 1;
			break;
		case 'H':
			val += 1;
			break;
		}
		if(val < 0)
		{
			ans = max(ans, len);
			val = len = 0;
		}
	}
	ans = max(ans, len);
	printf("%d\n", ans);
	exit(0);
}
