#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1 << 17 | 1;
int t, n, m;
struct Segment {
	int zero, vmax, vmin;
} seg[maxn << 1| 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_build(int L, int R) {
	int rt = seg_idx(L, R);
	if(L == R) {
		int v;
		scanf("%d", &v);
		seg[rt].zero = !v;
		seg[rt].vmax = seg[rt].vmin = v;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_build(L, M);
	seg_build(M + 1, R);
	seg[rt].zero = seg[lch].zero || seg[rch].zero;
	seg[rt].vmax = max(seg[lch].vmax, seg[rch].vmax);
	seg[rt].vmin = min(seg[lch].vmin, seg[rch].vmin);
}
void seg_upd(int L, int R, int x, int v) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt].zero = !v;
		seg[rt].vmax = seg[rt].vmin = v;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(x <= M)
		seg_upd(L, M, x, v);
	else
		seg_upd(M + 1, R, x, v);
	seg[rt].zero = seg[lch].zero || seg[rch].zero;
	seg[rt].vmax = max(seg[lch].vmax, seg[rch].vmax);
	seg[rt].vmin = min(seg[lch].vmin, seg[rch].vmin);
}
Segment seg_que(int L, int R, int l, int r) {
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
		return seg[rt];
	int M = (L + R) >> 1;//, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(r <= M)
		return seg_que(L, M, l, r);
	if(M < l)
		return seg_que(M + 1, R, l, r);
	Segment A = seg_que(L, M, l, r), B = seg_que(M + 1, R, l, r);
	A.zero = A.zero || B.zero;
	A.vmax = max(A.vmax, B.vmax);
	A.vmin = min(A.vmin, B.vmin);
	return A;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		n = 1 << n;
		seg_build(0, n - 1);
		scanf("%d", &m);
		while(m--) {
			int typ, x, y;
			scanf("%d%d%d", &typ, &x, &y);
			if(typ == 1) {
				Segment res = seg_que(0, n - 1, x, y);
				if(res.vmax > 0 && res.vmin < 0) { // has negative
					printf("%lld\n", (long long)res.vmax * res.vmin);
				} else if(res.zero) { // has zero
					puts("0");
				} else { // has positive
					printf("%lld\n", min((long long)res.vmax * res.vmax, (long long)res.vmin * res.vmin));
				}
			} else {
				seg_upd(0, n - 1, x, y);
			}
		}
	}
	return 0;
}
