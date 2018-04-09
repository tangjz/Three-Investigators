#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>
#include <bitset>
#include <cassert>

using namespace std;

const int NMAX = 100, BRUTE = 40;
const int VMAX = 10000 * BRUTE / 2 + 1;

int N, ans, limit;
int A[NMAX], sum[NMAX];
int f[NMAX][NMAX], g[NMAX][NMAX];
set<int> h[NMAX];
set<int>::iterator tmp;
bitset<VMAX> pack[2][NMAX];

inline void child(int &l, int &r)
{
	if(A[l] > A[r] || A[l] == A[r])
		l += 1;
	else
		r -= 1;
}

void solve(int l, int r, int cur)
{
	if(r - l + 1 <= BRUTE)
	{
		tmp = h[l].upper_bound(limit - cur);
		if(tmp == h[l].begin())
			return;
		else
			tmp--;
		//ans = max(ans, *tmp);
		return;
	}
	if(cur + f[l][r] <= limit)
	{
		ans = max(ans, cur + f[l][r]);
		return;
	}
	if(cur + g[l][r] > limit)
		return;
	child(l, r);
	solve(l, r - 1, cur + A[r]);
	solve(l + 1, r, cur + A[l]);
}

int main()
{
	int i, j, l, r;
	bitset<VMAX> *cur, *nxt;
	while(scanf("%d", &N) != EOF)
	{
		ans = 0;
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		for(i = 0;i < NMAX;i += 1)
		{
			pack[0][i].reset();
			pack[1][i].reset();
		}
		for(i = 1;i <= N;i += 1)
		{
			scanf("%d", &A[i]);
			//assert(A[i] <= 10000);
			sum[i] = sum[i - 1] + A[i];
		}
		for(i = 1;i <= N;i += 1)
			h[i].clear();
		limit = (sum[N] - 1) / 2;
		cur = pack[0];
		nxt = pack[1];
		for(j = 2;j <= N;j += 2)
		{
			for(i = 1;i + j - 1 <= N;i += 1)
			{
				l = i;
				r = i + j - 1;
				child(l, r);
				f[i][i + j - 1] = max(f[l][r - 1] + A[r], f[l + 1][r] + A[l]);
				g[i][i + j - 1] = min(g[l][r - 1] + A[r], g[l + 1][r] + A[l]);
				if(j <= BRUTE)
				{
					if(j == 2)
						(nxt + i)->set(f[i][i + j - 1]);
					else
						*(nxt + i) = ((*(cur + l))<<A[r]) | ((*(cur + l + 1))<<A[l]);
				}
			}
			if(j <= BRUTE)
				swap(cur, nxt);
		}
		for(i = 1;i + min(N, BRUTE) - 1 <= N;i += 1)
		{
			for(j = 1;j < VMAX;j += 1)
			{
				if(cur[i][j])
					h[i].insert(j);
			}
		}
		solve(1, N, 0);
		if(!ans)
			printf("The child will be unhappy...\n");
		else
			printf("%d\n", sum[N] - 2 * ans);
	}
	exit(0);
}
