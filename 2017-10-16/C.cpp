#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1001, maxm = 63, maxq = 100001, mod = 1000210433;
int n, m, q, inv[maxn], f[maxn], g[maxn], tot, que[maxm], vL[maxm], vR[maxm], adt;
struct Event {
	int typ, L, R, low, upp;
} eve[maxq];
void solve() {
	static int ctr[maxn];
	adt = 0;
	memset(g, 0, sizeof g);
	bool ban = 0;
	for(int i = 1; !ban && i < tot; ++i)
		ban |= vL[i] > vR[i];
	if(ban)
		return;
	memset(ctr, 0, sizeof ctr);
	for(int i = 1; i < tot; ++i) {
		adt = min((LL)maxn, adt + (LL)(que[i] - que[i - 1]) * vL[i]);
		if(vR[i] - vL[i] + 1 < maxn)
			ctr[vR[i] - vL[i] + 1] += que[i] - que[i - 1];
	}
	for(int i = maxn - 1; i >= 1; --i) {
		ctr[i] = (LL)i * (mod - ctr[i]) % mod;
		for(int j = i; j < maxn; j += i)
			(g[j] += ctr[i]) >= mod && (g[j] -= mod);
	}
	ctr[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		ctr[i] = g[i];
		for(int j = 1; j < i; ++j)
			ctr[i] = (ctr[i] + (LL)g[j] * ctr[i - j]) % mod;
		ctr[i] = (LL)ctr[i] * inv[i] % mod;
	}
	for(int i = 0; i < maxn; ++i) {
		g[i] = 0;
		for(int j = 0; j <= i; ++j)
			g[i] = (g[i] + (LL)f[j] * ctr[i - j]) % mod;
	}
}
int main() {
	scanf("%d%d%d", &n, &m, &q);
	que[tot++] = 0;
	que[tot++] = n;
	for(int i = 0; i < q; ++i) {
		scanf("%d", &eve[i].typ);
		if(eve[i].typ == 1) {
			scanf("%d%d%d%d", &eve[i].L, &eve[i].R, &eve[i].low, &eve[i].upp);
			que[tot++] = eve[i].L - 1;
			que[tot++] = eve[i].R; // (L - 1, R]
		} else { // 2
			scanf("%d", &eve[i].upp);
		}
	}
	sort(que, que + tot);
	tot = unique(que, que + tot) - que;
	for(int i = 1; i < tot; ++i) {
		vL[i] = 0;
		vR[i] = maxn;
	}
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	f[0] = 1;
	for(int i = 1; i < maxn; ++i)
		f[i] = (LL)f[i - 1] * (n - 1 + i) % mod * inv[i] % mod;
	solve();
	for(int i = 0; i < q; ++i) {
		if(eve[i].typ == 1) {
			eve[i].L = lower_bound(que, que + tot, eve[i].L - 1) - que + 1;
			eve[i].R = lower_bound(que, que + tot, eve[i].R) - que;
			for(int j = eve[i].L; j <= eve[i].R; ++j) {
				vL[j] = eve[i].low;
				vR[j] = eve[i].upp;
			}
			solve();
		} else { // 2
			m = eve[i].upp;
		}
		printf("%d\n", m >= adt ? g[m - adt] : 0);
	}
	return 0;
}
