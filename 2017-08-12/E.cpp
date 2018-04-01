#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int LMAX = 1000100;

int N, L;
char str[LMAX];
int cid;
int fail[LMAX], candi[LMAX];

void buildKMP()
{
	int i, j;
	for(i = 2, j = 0;str[i];i += 1)
	{
		while(j && str[j + 1] != str[i])
			j = fail[j];
		if(str[j + 1] == str[i])
			j += 1;
		fail[i] = j;
		//printf("fail[%d]: %d\n", i, fail[i]);
	}
}

bool check(int x)
{
	int i, pos;
	//printf("check: %d\n", x);
	for(i = 2, pos = 0;i <= L - x;i += 1)
	{
		while(pos && str[pos + 1] != str[i])
			pos = fail[pos];
		if(str[pos + 1] == str[i])
			pos += 1;
		//printf("1 i:%d, pos: %d\n", i, pos);
		if(i <= x || i - pos < x || pos > x)
			pos = fail[pos];
		//printf("2 i:%d, pos: %d\n", i, pos);
		if(pos == x)
			return true;
	}
	return false;
}

int main()
{
	int i, pos, l, r, mid;
	scanf("%d", &N);
	for(i = 1;i <= N;i += 1)
	{
		cid = 0;
		scanf("%s", str + 1);
		L = strlen(str + 1);
		//printf("L:%d\n", L);
		buildKMP();
		pos = L;
		candi[cid++] = pos;
		while(pos)
		{
			//printf("pos: %d\n", pos);
			pos = fail[pos];
			if(pos * 3 <= L)
			{
				//printf("candi:%d\n", pos);
				candi[cid++] = pos;
			}
		}
		l = 0;
		r = cid;
		while(l + 1 < r)//(]
		{
			mid = (l + r)>>1;
			if(check(candi[mid]))
				r = mid;
			else
				l = mid;
		}
		printf("%d\n", candi[r]);
	}
	exit(0);
}
