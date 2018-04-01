#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 100001, INF = 0x3f3f3f3f;
int n, m, q;
long long ans;
struct Segment {
	int minv, posL, posR, minL, minR;
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
inline void seg_up(int rt, int lch, int rch) {
	if(seg[lch].minv == seg[rch].minv) {
		seg[rt].minv = seg[lch].minv;
		seg[rt].posL = seg[lch].posL;
		seg[rt].posR = seg[rch].posR;
	} else if(seg[lch].minv < seg[rch].minv) {
		seg[rt].minv = seg[lch].minv;
		seg[rt].posL = seg[lch].posL;
		seg[rt].posR = seg[lch].posR;
	} else {
		seg[rt].minv = seg[rch].minv;
		seg[rt].posL = seg[rch].posL;
		seg[rt].posR = seg[rch].posR;
	}
	seg[rt].minL = min(seg[lch].minL, seg[rch].minL);
	seg[rt].minR = min(seg[lch].minR, seg[rch].minR);
}
inline void seg_init(int L, int R) {
	int rt = seg_idx(L, R);
	if(L == R) {
		scanf("%d", &seg[rt].minv);
		ans += seg[rt].minv;
		seg[rt].posL = seg[rt].posR = L;
		seg[rt].minL = m + 1 + L;
		seg[rt].minR = m + 1 - L;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_init(L, M);
	seg_init(M + 1, R);
	seg_up(rt, lch, rch);
}
inline void seg_upd(int L, int R, int x, int v) {
	int rt = seg_idx(L, R);
	if(L == R) {
		ans += v - seg[rt].minv;
		seg[rt].minv = v;
		--seg[rt].minL;
		--seg[rt].minR;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(x <= M)
		seg_upd(L, M, x, v);
	else
		seg_upd(M + 1, R, x, v);
	seg_up(rt, lch, rch);
}
inline pair<int, int> seg_lft(int L, int R, int x, int &pre) {
	if(x < R) {
		int M = (L + R) >> 1;
		if(x <= M)
			return seg_lft(L, M, x, pre);
		pair<int, int> ret = seg_lft(M + 1, R, x, pre);
		if(pre > x + 1) {
			pair<int, int> tmp = seg_lft(L, M, x, pre);
			if(ret.first > tmp.first)
				ret = tmp;
		}
		return ret;
	} else {
		int rt = seg_idx(L, R);
		pair<int, int> ret = make_pair(INF, -1);
		if(seg[rt].minL > x + (L < R)) {
			ret = make_pair(seg[rt].minv, seg[rt].posR);
		} else if(L < R && pre > x + 1) {
			int M = (L + R) >> 1;
			ret = seg_lft(M + 1, R, x, pre);
			if(pre > x + 1) {
				pair<int, int> tmp = seg_lft(L, M, x, pre);
				if(ret.first > tmp.first)
					ret = tmp;
			}
		}
		pre = min(pre, seg[rt].minL);
		return ret;
	}
}
inline pair<int, int> seg_rht(int L, int R, int x, int &pre) {
	if(L < x) {
		int M = (L + R) >> 1;
		if(M < x)
			return seg_rht(M + 1, R, x, pre);
		pair<int, int> ret = seg_rht(L, M, x, pre);
		if(pre > -x + 1) {
			pair<int, int> tmp = seg_rht(M + 1, R, x, pre);
			if(ret.first > tmp.first)
				ret = tmp;
		}
		return ret;
	} else {
		int rt = seg_idx(L, R);
		pair<int, int> ret = make_pair(INF, -1);
		if(seg[rt].minR > -x + (L < R)) {
			ret = make_pair(seg[rt].minv, seg[rt].posL);
		} else if(L < R && pre > -x + 1) {
			int M = (L + R) >> 1;
			ret = seg_rht(L, M, x, pre);
			if(pre > -x + 1) {
				pair<int, int> tmp = seg_rht(M + 1, R, x, pre);
				if(ret.first > tmp.first)
					ret = tmp;
			}
		}
		pre = min(pre, seg[rt].minR);
		return ret;
	}
}
int main() {
	scanf("%d%d", &n, &m);
	seg_init(1, n);
	scanf("%d", &q);
	while(q--) {
		int pos, val, tp1 = INF, tp2 = INF;
		scanf("%d%d", &pos, &val);
		pair<int, int> lft = seg_lft(1, n, pos, tp1), rht = seg_rht(1, n, pos, tp2);
		seg_upd(1, n, lft.first < rht.first || (lft.first == rht.first && pos - lft.second <= rht.second - pos) ? lft.second : rht.second, val);
		printf("%lld\n", ans);
	}
	return 0;
}
