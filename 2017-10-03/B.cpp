#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int table[10][10];
int d[5], ans;
bool invalid[10000];

int check()
{
	int i, res = 0;
	for(i = 4;i >= 0;i -= 1)
		res = table[res][d[i]];
	return res;
}

int main()
{
	int i, j, k, x;
	for(i = 0;i < 10;i += 1)
	{
		for(j = 0;j < 10;j += 1)
			scanf("%d", &table[i][j]);
	}
	for(i = 0;i < 10000;i += 1)
	{
		for(j = 1, x = i;j <= 4;j += 1, x /= 10)
			d[j] = x % 10;
		for(j = 4, x = 0;j;j -= 1)
			x = table[x][d[j]];
		d[j] = x;
		for(j = 0;j <= 4 && !invalid[i];j += 1)
		{
			x = d[j];
			for(k = 0;k < 10 && !invalid[i];k += 1)
			{
				if(k == d[j])
					continue;
				d[j] = k;
				if(!check())
					invalid[i] = true;
				d[j] = x;
			}
		}
		for(j = 0;j < 4 && !invalid[i];j += 1)
		{
			if(d[j] != d[j + 1])
			{
				swap(d[j], d[j + 1]);
				if(!check())
					invalid[i] = true;
				swap(d[j], d[j + 1]);
			}
		}
		if(invalid[i])
			ans += 1;
	}
	printf("%d\n", ans);
	exit(0);
}

