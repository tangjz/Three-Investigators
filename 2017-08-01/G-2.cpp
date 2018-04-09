#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int VMAX = 810, OMAX = 810;
const int MMAX = 10;

struct Operation
{
	int a;
	int b;
	int c;
};

int M, ONE;
int vid, oid;
int init[VMAX], check[2][VMAX];
int out, in[MMAX], nin[MMAX];
int trie[VMAX];
Operation op[OMAX];

void addOp(int a, int b, int c)
{
	op[++oid] = (Operation){a, b, c};
}

int main()
{
	int i, j, x, y;
	char c;
	while(scanf("%d", &M) != EOF)
	{
		oid = check[0][0] = check[1][0] = 0;
		vid = M;
		for(i = 0;i < (1<<M);i += 1)
		{
			for(j = x = 0;j < M;j += 1)
			{
				//scanf(" %c", &c);
				c = ((i>>j) & 1) + '0';
				x = (x<<1) | (c - '0');
			}
			//scanf("%d", &y);
			y = i & 1;
			check[y][++check[y][0]] = x;
		}
		init[out = ++vid] = check[0][0] <= check[1][0]?0:1;
		init[ONE = ++vid] = 1;
		for(i = 1;i <= M;i += 1)
		{
			in[i] = i;
			init[nin[i] = ++vid] = 1;
			addOp(ONE, in[i], nin[i]);
		}
		trie[1] = ONE;
		for(i = 1;i <= M;i += 1)
		{
			for(j = 0;j < (1<<i);j += 1)
			{
				init[trie[x = (1<<i) + j] = ++vid] = 0;
				addOp(trie[x>>1], (x & 1)?in[i]:nin[i], trie[x]);
			}
		}
		init[++vid] = 1;
		for(i = 1;i <= check[init[out]][0];i += 1)
		{
			init[++vid] = 1;
			addOp(trie[(1<<M) + check[init[out]][i]], ONE, vid);
			init[++vid] = 0;
			addOp(vid - 2, vid - 1, vid);
		}
		addOp(vid, ONE, out);
		printf("%d\n", init[out]);
		printf("%d\n", vid - M - 1);
		for(i = M + 2;i <= vid;i += 1)
			printf("%d\n", init[i]);
		printf("%d\n", oid);
		for(i = 1;i <= oid;i += 1)
			printf("%d %d %d\n", op[i].a, op[i].b, op[i].c);
	}
	exit(0);
}
