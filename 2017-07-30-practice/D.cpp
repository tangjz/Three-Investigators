#include <cstdio>
#include <algorithm>
const int maxn = 100001, maxs = 1800001;
int n, m, q, a[maxn], que[maxn], tot, rt[maxn], pL[maxs], pR[maxs], cnt[maxs];
void seg_upd(int &rt, int L, int R, int x, int v) {
	pL[tot] = pL[rt];
	pR[tot] = pR[rt];
	cnt[tot] = cnt[rt] + 1;
	rt = tot++;
	if(L == R)
		return;
	int M = (L + R) >> 1;
	if(x <= M)
		seg_upd(pL[rt], L, M, x, v);
	else
		seg_upd(pR[rt], M + 1, R, x, v);
}
int seg_que(int rtL, int rtR, int L, int R, int k) {
	while(L < R) {
		int M = (L + R) >> 1;
		if(cnt[pL[rtR]] - cnt[pL[rtL]] < k) {
			k -= cnt[pL[rtR]] - cnt[pL[rtL]];
			L = M + 1;
			rtL = pR[rtL];
			rtR = pR[rtR];
		} else {
			R = M;
			rtL = pL[rtL];
			rtR = pL[rtR];
		}
	}
	return L;
}
int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		que[i] = a[i];
	}
	std::sort(que + 1, que + n + 1);
	m = std::unique(que + 1, que + n + 1) - que - 1;
	tot = 1;
	for(int i = 1; i <= n; ++i) {
		rt[i] = rt[i - 1];
		seg_upd(rt[i], 1, m, std::lower_bound(que + 1, que + m + 1, a[i]) - que, 1);
	}
	while(q--) {
		int L, R, k;
		scanf("%d%d%d", &L, &R, &k);
		printf("%d\n", que[seg_que(rt[L - 1], rt[R], 1, m, k)]);
	}
	return 0;
}
