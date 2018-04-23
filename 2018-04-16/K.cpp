#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, x[maxn], y[maxn];
struct Seg {
	int xMx1, xMx2, yMx1, yMx2;
	int xMn1, xMn2, yMn1, yMn2;
	Seg merge(Seg const &t) const {
		Seg ret = *this;
		if(x[ret.xMx1] <= x[t.xMx1]) {
			ret.xMx2 = ret.xMx1;
			ret.xMx1 = t.xMx1;
			if(ret.xMx2 == -1 || t.xMx2 != -1 && x[ret.xMx2] <= x[t.xMx2])
				ret.xMx2 = t.xMx2;
		} else if(ret.xMx2 == -1 || x[ret.xMx2] <= x[t.xMx1]) {
			ret.xMx2 = t.xMx1;
		}
		if(y[ret.yMx1] <= y[t.yMx1]) {
			ret.yMx2 = ret.yMx1;
			ret.yMx1 = t.yMx1;
			if(ret.yMx2 == -1 || t.yMx2 != -1 && y[ret.yMx2] <= y[t.yMx2])
				ret.yMx2 = t.yMx2;
		} else if(ret.yMx2 == -1 || y[ret.yMx2] <= y[t.yMx1]) {
			ret.yMx2 = t.yMx1;
		}
		if(x[ret.xMn1] >= x[t.xMn1]) {
			ret.xMn2 = ret.xMn1;
			ret.xMn1 = t.xMn1;
			if(ret.xMn2 == -1 || t.xMn2 != -1 && x[ret.xMn2] >= x[t.xMn2])
				ret.xMn2 = t.xMn2;
		} else if(ret.xMn2 == -1 || x[ret.xMn2] >= x[t.xMn1]) {
			ret.xMn2 = t.xMn1;
		}
		if(y[ret.yMn1] >= y[t.yMn1]) {
			ret.yMn2 = ret.yMn1;
			ret.yMn1 = t.yMn1;
			if(ret.yMn2 == -1 || t.yMn2 != -1 && y[ret.yMn2] >= y[t.yMn2])
				ret.yMn2 = t.yMn2;
		} else if(ret.yMn2 == -1 || y[ret.yMn2] >= y[t.yMn1]) {
			ret.yMn2 = t.yMn1;
		}
		return ret;
	}
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
int seg_build(int L, int R) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt] = (Seg){L, -1, L, -1, L, -1, L, -1};
	} else {
		int M = (L + R) >> 1;
		seg[rt] = seg[seg_build(L, M)].merge(seg[seg_build(M + 1, R)]);
	}
	return rt;
}
Seg seg_que(int L, int R, int l, int r) {
	if(l <= L && R <= r)
		return seg[seg_idx(L, R)];
	int M = (L + R) >> 1;
	if(r <= M)
		return seg_que(L, M, l, r);
	if(l > M)
		return seg_que(M + 1, R, l, r);
	return seg_que(L, M, l, r).merge(seg_que(M + 1, R, l, r));
}
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		for(int i = 1; i <= n; ++i)
			scanf("%d%d", x + i, y + i);
		seg_build(1, n);
		while(m--) {
			int L, R;
			scanf("%d%d", &L, &R);
			Seg cur = seg_que(1, n, L, R);
			int tot = 4, seq[5] = {cur.xMx1, cur.xMn1, cur.yMx1, cur.yMn1};
			sort(seq, seq + tot);
			tot = unique(seq, seq + tot) - seq;
			int ans = max(x[cur.xMx1] - x[cur.xMn1], y[cur.yMx1] - y[cur.yMn1]);
			for(int i = 0; i < tot; ++i) {
				int xMx = seq[i] == cur.xMx1 ? cur.xMx2 : cur.xMx1;
				int yMx = seq[i] == cur.yMx1 ? cur.yMx2 : cur.yMx1;
				int xMn = seq[i] == cur.xMn1 ? cur.xMn2 : cur.xMn1;
				int yMn = seq[i] == cur.yMn1 ? cur.yMn2 : cur.yMn1;
				ans = min(ans, max(x[xMx] - x[xMn], y[yMx] - y[yMn]));
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
