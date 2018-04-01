#include <cstdio>
#include <algorithm>
const int maxn = 300001;
int n, L[maxn], seg[maxn << 1];
inline int seg_idx(int L, int R)
{
	return (L + R) | (L < R);
}
void update(int L, int R, int x, int v)
{
	int rt = seg_idx(L, R);
	if(L == R)
	{
		seg[rt] = v;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(x <= M)
		update(L, M, x, v);
	else
		update(M + 1, R, x, v);
	seg[rt] = std::min(seg[lch], seg[rch]);
}
int find(int L, int R, int v)
{
	while(L < R)
	{
		int M = (L + R) >> 1, lch = seg_idx(L, M);
		if(seg[lch] <= v)
			R = M;
		else
			L = M + 1;
	}
	return L;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		int c, x;
		scanf("%d", &c);
		while(c--)
		{
			scanf("%d", &x);
			if(!L[x])
				L[x] = i;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		int x = L[i] ? find(1, n, L[i]) : 1;
		update(1, n, x, i);
		printf("%d%c", x, " \n"[i == n]);
	}
	return 0;
}
