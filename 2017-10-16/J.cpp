#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = 100001, maxm = 2001, maxd = 1 << 16 | 1, maxs = 1563;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, m, lim, tim[maxm], sz[maxm], ord[maxm], Log[maxd];
ULL msk[maxs], tmp[maxs];
inline int getLog(ULL x) {
	int ret = 0;
	if(x >> 32) {
		x >>= 32;
		ret |= 32;
	}
	if(x >> 16) {
		x >>= 16;
		ret |= 16;
	}
	return ret | Log[x];
}
inline int findPos(int lim) {
	int px = lim >> 6, py = lim & 63;
	if(py < 63 && msk[px] & ((1ULL << (py + 1)) - 1))
		return px << 6 | getLog(msk[px] & ((1ULL << (py + 1)) - 1));
	for(px -= py < 63; px >= 0; --px)
		if(msk[px])
			return px << 6 | getLog(msk[px]);
	return -1;
}
inline void shiftLeft(ULL src[], int dt, ULL dst[]) {
	int dx = dt >> 6, dy = dt & 63;
	for(int i = 0; i < maxs; ++i) {
		dst[i] = 0;
		if(i >= dx) {
			dst[i] |= src[i - dx] << dy;
			if(dy && i > dx)
				dst[i] |= src[i - dx - 1] >> (64 - dy);
		}
	}
}
int main() {
	for(int i = 2; i < maxd; ++i)
		Log[i] = Log[i >> 1] + 1;
	scanf("%d%d%d", &n, &m, &lim);
	for(int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		tim[x] = i;
		++sz[x];
	}
	if(n > lim * 2) {
		puts("-1");
		return 0;
	} // now, n <= lim * 2
	for(int i = 1; i <= m; ++i)
		ord[i] = i;
	sort(ord + 1, ord + m + 1, [&](int const &u, int const &v) {
		return tim[u] < tim[v];
	});
	LL ans = n <= lim ? (LL)n * n : INF; // choose one shuffle
	msk[0] = 1;
	for(int i = 1; i <= m; ++i) { // choose two shuffles
		int o = ord[i];
		if(!tim[o] || sz[o] > lim)
			continue;
		int lft = sz[o] + findPos(lim - sz[o]);
		if(lft >= sz[o] && n - lft <= lim)
			ans = min(ans, (LL)tim[o] * lft + (LL)n * (n - lft));
		shiftLeft(msk, sz[o], tmp);
		for(int j = 0; j < maxs; ++j)
			msk[j] |= tmp[j];
	}
	if(ans < INF)
		printf("%lld\n", ans);
	else
		puts("-1");
	return 0;
}
