#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int hit, tot;
int cache[64];

int c2i(char c)
{
	if('A' <= c && c <= 'F')
		return c - 'A' + 10;
	if('a' <= c && c <= 'f')
		return c - 'a' + 10;
	return c - '0';
}

int main()
{
	int i, addr;
	char str[20] = {};
	memset(cache, -1, sizeof(cache));
	while(1)
	{
		scanf("%s", str);
		if(!strcmp(str, "END"))
			break;
		addr = 0;
		for(i = 0;i < 7;i += 1)
			addr = (addr<<4) + c2i(str[i]);
		addr = addr>>4;
		if(cache[addr & ((1<<6) - 1)] < 0 || cache[addr & ((1<<6) - 1)] != addr)
		{
			cache[addr & ((1<<6) - 1)] = addr;
			printf("Miss\n");
		}
		else
		{
			hit += 1;
			printf("Hit\n");
		}
		tot += 1;
	}
	printf("Hit ratio = %.2f%%\n", (double)hit / tot * 100);
	exit(0);
}
