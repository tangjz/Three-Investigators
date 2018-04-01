#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 3, maxd = 11, mod = 10;
int t, n, m, a[maxn], tot, seq[maxn], pos[maxn], bit[maxd][maxn];
struct Query {
	int idx, L, R;
	bool operator < (Query const &t) const {
		return R < t.R;
	}
} que[maxn];
char ans[maxn][maxd];
void bit_upd(int bit[], int x, int v) {
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
int bit_que(int bit[], int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		memset(bit, 0, sizeof bit);
		scanf("%d%d", &n, &m);
		for(int i = 1; i < maxd; ++i)
			memset(bit[i] + 1, 0, n * sizeof(int));
	    tot = 0;
	    for(int i = 1; i <= n; ++i) {
	        scanf("%d", a + i);
	        seq[tot++] = a[i];
	    }
	    sort(seq, seq + tot);
	    tot = unique(seq, seq + tot) - seq;
	    memset(pos, 0, tot * sizeof(int));
		for(int i = 1; i <= m; ++i) {
			que[i].idx = i;
			scanf("%d%d", &que[i].L, &que[i].R);
		}
		sort(que + 1, que + m + 1);
		for(int i = 1, j = 1; i <= n; ++i) {
	    	int idx = lower_bound(seq, seq + tot, a[i]) - seq, idxL = idx - 1, idxR = idx + 1;
	        int las = pos[idx], lft = 0, rht = 0, pre, cur = i;
			while(cur > las && (lft < maxd || rht < maxd)) {
				pre = cur;
				cur = las;
	            if(lft < maxd && idxL >= 0 && seq[idxL] == a[i] - lft - 1)
	                cur = max(cur, pos[idxL]);
	            if(rht < maxd && idxR < tot && seq[idxR] == a[i] + rht + 1)
	                cur = max(cur, pos[idxR]);
				if(lft && lft < maxd) {
					bit_upd(bit[lft], cur + 1, -1);
					bit_upd(bit[lft], pre + 1, 1);
				}
				if(rht && rht < maxd) {
					bit_upd(bit[rht], cur + 1, -1);
					bit_upd(bit[rht], pre + 1, 1);
				}
				if(lft + rht + 1 < maxd) {
					bit_upd(bit[lft + rht + 1], cur + 1, 1);
					bit_upd(bit[lft + rht + 1], pre + 1, -1);
				}
	            for( ; lft < maxd && idxL >= 0 && seq[idxL] == a[i] - lft - 1 && pos[idxL] >= cur; ++lft, --idxL);
	            for( ; rht < maxd && idxR < tot && seq[idxR] == a[i] + rht + 1 && pos[idxR] >= cur; ++rht, ++idxR);
			}
			for(pos[idx] = i; j <= m && que[j].R == i; ++j)
				for(int k = 1; k < maxd; ++k)
					ans[que[j].idx][k - 1] = '0' + bit_que(bit[k], que[j].L) % mod;
		}
		for(int i = 1; i <= m; ++i)
			puts(ans[i]);
	}
	return 0;
}
