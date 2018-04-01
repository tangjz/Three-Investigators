#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <bitset>

using namespace std;

const int NMAX = 1100, SMAX = 110;

int T, N;
char S[SMAX];
string pre[NMAX][2], suf[NMAX][2];
bitset<SMAX> mask[NMAX][2];

bool match(int len, bitset<SMAX> &x, bitset<SMAX> &y)
{
	return ((x<<(SMAX - len))>>(SMAX - len)) == y;
}

int main()
{
	int t, i, j, k, s;
	int len;
	bitset<SMAX> l, r;
	bool flag;
	pre[0][0] = suf[0][0] = 'L';
	pre[0][1] = suf[0][1] = 'R';
	mask[0][1].set(0);
	for(i = 1;i <= 1000;i += 1)
	{
		pre[i][0] = (pre[i - 1][0] + 'L' + pre[i - 1][1]).substr(0, SMAX);
		suf[i][0] = suf[i - 1][0] + 'L' + suf[i - 1][1];
		suf[i][0] = suf[i][0].substr(max(0, (int)suf[i][0].size() - SMAX), SMAX);
		pre[i][1] = (pre[i - 1][0] + 'R' + pre[i - 1][1]).substr(0, SMAX);
		suf[i][1] = suf[i - 1][0] + 'R' + suf[i - 1][1];
		suf[i][1] = suf[i][1].substr(max(0, (int)suf[i][1].size() - SMAX), SMAX);
		for(j = 0;j < suf[i][0].size();j += 1)
		{
			if(suf[i][0][j] == 'R')
				mask[i][0].set(suf[i][0].size() - 1 - j);
		}
		for(j = 0;j < pre[i][1].size();j += 1)
		{
			if(pre[i][1][j] == 'R')
				mask[i][1].set(j);
		}
	}
	scanf("%d", &T);
	for(t = 1;t <= T;t += 1)
	{
		scanf("%d %s", &N, S);
		len = strlen(S);
		flag = false;
		for(j = 0;j < N;j += 1)
		{
			if(!j)
				s = 0;
			else
				s = (1<<j) - 1;
			l.reset();
			r.reset();
			for(k = 1;k < len;k += 1)
			{
				if(S[k] == 'R')
					r.set(k - 1);
			}
			for(k = 0;k < len;k += 1)
			{
				if(k <= s && len - k - 1 <= s
					&& (j + 1 != N || S[k] == 'L'))
				{
					if(!j)
						flag = true;
					else
						flag = flag || (match(k, mask[j - 1][0], l) && match(len - k - 1, mask[j - 1][1], r));
				}
				l = l<<1;
				if(S[k] == 'R')
					l.set(0);
				r = r>>1;
			}
		}
		printf("Case %d: %s\n", t, flag?"Yes":"No");
	}
	exit(0);
}
