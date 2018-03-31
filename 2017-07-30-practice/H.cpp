#include <vector>
#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 200001, mod = (int)1e9 + 7;
int n, q, a[maxn], fa[maxn], tot, in[maxn], out[maxn];
std::vector<int> e[maxn];
int inv[maxn], deg[maxn];
struct Query {
	int typ, idx;
} que[maxn];
struct Segment {
	int sum, prd;
} seg[maxn << 1 | 1];
void dfs(int u) {
	in[u] = ++tot;
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		dfs(*it);
	out[u] = tot;
}
inline int mod_inv(int x) {
	return x <= n ? inv[x] : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
inline void seg_up(Segment &rt, Segment lch, Segment rch) {
	(rt.sum = lch.sum + rch.sum) >= mod && (rt.sum -= mod);
}
inline void seg_down(Segment &rt, Segment &lch, Segment &rch) {
	if(rt.prd > 1) {
		lch.sum = (LL)lch.sum * rt.prd % mod;
		lch.prd = (LL)lch.prd * rt.prd % mod;
		rch.sum = (LL)rch.sum * rt.prd % mod;
		rch.prd = (LL)rch.prd * rt.prd % mod;
		rt.prd = 1;
	}
}
void seg_init(int L, int R) {
	seg[seg_idx(L, R)] = (Segment){0, 1};
	if(L == R)
		return;
	int M = (L + R) >> 1;
	seg_init(L, M);
	seg_init(M + 1, R);
}
void seg_set(int L, int R, int x, int v) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt].sum = v;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_down(seg[rt], seg[lch], seg[rch]);
	x <= M ? seg_set(L, M, x, v) : seg_set(M + 1, R, x, v);
	seg_up(seg[rt], seg[lch], seg[rch]);
}
void seg_mul(int L, int R, int l, int r, int prd) {
	int rt = seg_idx(L, R);
	if(l <= L && R <= r) {
		seg[rt].sum = (LL)seg[rt].sum * prd % mod;
		seg[rt].prd = (LL)seg[rt].prd * prd % mod;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_down(seg[rt], seg[lch], seg[rch]);
	if(l <= M)
		seg_mul(L, M, l, r, prd);
	if(M < r)
		seg_mul(M + 1, R, l, r, prd);
	seg_up(seg[rt], seg[lch], seg[rch]);
}
int seg_que(int L, int R, int l, int r) {
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
		return seg[rt].sum;
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R), ret = 0;
	seg_down(seg[rt], seg[lch], seg[rch]);
	if(l <= M)
		(ret += seg_que(L, M, l, r)) >= mod && (ret -= mod);
	if(M < r)
		(ret += seg_que(M + 1, R, l, r)) >= mod && (ret -= mod);
	seg_up(seg[rt], seg[lch], seg[rch]);
	return ret;
}
int main() {
	scanf("%d%d", a + (++n), &q);
	for(int i = 0; i < q; ++i) {
		int &typ = que[i].typ, &idx = que[i].idx;
		scanf("%d", &typ);
		if(typ == 1) {
			idx = ++n;
			scanf("%d%d", fa + n, a + n);
			e[fa[n]].push_back(n);
		} else {
			scanf("%d", &idx);
		}
	}
	inv[1] = 1;
	for(int i = 2; i <= n; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	tot = 0;
	dfs(1);
	seg_init(1, n);
	deg[1] = 1;
	seg_set(1, n, 1, a[1]);
	for(int i = 0; i < q; ++i) {
		int &typ = que[i].typ, &idx = que[i].idx;
		if(typ == 1) {
			++deg[fa[idx]];
			seg_mul(1, n, in[fa[idx]], in[idx] - 1, (LL)deg[fa[idx]] * inv[deg[fa[idx]] - 1] % mod);
			deg[idx] = 1;
			seg_set(1, n, in[idx], (LL)seg_que(1, n, in[fa[idx]], in[fa[idx]]) * mod_inv(a[fa[idx]]) % mod * a[idx] % mod);
		} else {
			int ans = seg_que(1, n, in[idx], out[idx]);
			if(fa[idx])
				ans = (LL)mod_inv(seg_que(1, n, in[fa[idx]], in[fa[idx]])) * a[fa[idx]] % mod * ans % mod;
			printf("%d\n", ans);
		}
	}
	return 0;
}
