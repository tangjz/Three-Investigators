#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000001, maxm = 10000001, maxq = 100001, INF = ~0u >> 1;
int t, q, tot, cnt, root[maxq], n, seq[maxn], stp;
struct Treap {
	int lch, rch, size, val, min;
} pool[maxm];
inline int randL() {
	return RAND_MAX == 0x7FFF ? rand() << 15 | rand() : rand();
}
inline int Snapshot(int rt) {
	// assert(tot < maxm);
	pool[tot] = pool[rt];
	return tot++;
}
void Maintain(int rt) {
	int lch = pool[rt].lch, rch = pool[rt].rch;
	pool[rt].size = pool[lch].size + pool[rch].size + 1;
	pool[rt].min = min(pool[rt].val, min(pool[lch].min, pool[rch].min));
}
pair<int, int> Split(int rt, int sz) {
	if(!rt)
		return make_pair(0, 0);
	int lch = pool[rt].lch, rch = pool[rt].rch;
	rt = Snapshot(rt);
	if(pool[lch].size + 1 > sz) {
		pair<int, int> tr = Split(lch, sz);
		pool[rt].lch = tr.second;
		Maintain(rt);
		return make_pair(tr.first, rt);
	} else {
		pair<int, int> tr = Split(rch, sz - pool[lch].size - 1);
		pool[rt].rch = tr.first;
		Maintain(rt);
		return make_pair(rt, tr.second);
	}
}
int Merge(int x, int y) {
	if(!x || !y) {
		return x | y;
	} else if(randL() % (pool[x].size + pool[y].size) < pool[x].size) {
		x = Snapshot(x);
		pool[x].rch = Merge(pool[x].rch, y);
		Maintain(x);
		return x;
	} else {
		y = Snapshot(y);
		pool[y].lch = Merge(x, pool[y].lch);
		Maintain(y);
		return y;
	}
}
int Segment(int rt, int L, int R) {
	return L <= R ? Split(Split(rt, R).first, L - 1).second : 0;
}
int Build(int sz, int a[]) {
	if(!sz)
		return 0;
	// assert(tot < maxm);
	int half = (sz - 1) >> 1, rt = tot++;
	pool[rt].lch = Build(half, a);
	pool[rt].val = a[half];
	pool[rt].rch = Build(sz - half - 1, a + half + 1);
	Maintain(rt);
	return rt;
}
int GetVal(int rt, int pos) {
	int lch = pool[rt].lch, rch = pool[rt].rch;
	if(pos <= pool[lch].size)
		return GetVal(lch, pos);
	if(pos == pool[lch].size + 1)
		return pool[rt].val;
	return GetVal(rch, pos - pool[lch].size - 1);
}
int EraseMin(int rt, int &pos) {
	int lch = pool[rt].lch, rch = pool[rt].rch;
	rt = Snapshot(rt);
	if(pool[rt].val == pool[rt].min) {
		pos = pool[lch].size + 1;
		pool[rt].val = INF;
	} else if(pool[lch].min == pool[rt].min) {
		pool[rt].lch = EraseMin(lch, pos);
	} else {
		pool[rt].rch = EraseMin(rch, pos);
		pos += pool[lch].size + 1;
	}
	Maintain(rt);
	return rt;
}
int main() {
	srand(time(0));
	scanf("%d", &t);
	// assert(1 <= t && t <= 6);
	while(t--) {
		tot = 1;
		pool[0].val = pool[0].min = INF;
		cnt = 0;
		scanf("%d", &q);
		// assert(1 <= q && q <= 100000);
		// int sum_n = 0, sum_k = 0;
		while(q--) {
			int typ;
			scanf("%d", &typ);
			// assert(1 <= typ && typ <= 3);
			if(typ == 1) {
				scanf("%d", &n);
				// assert((sum_n += n) <= 1000000);
				for(int i = 0; i < n; ++i) {
					scanf("%d", seq + i);
					// assert(0 <= seq[i] && seq[i] <= (int)1e9);
				}
				root[++cnt] = Build(n, seq);
			} else if(typ == 2) {
				int idx, L, R;
				scanf("%d%d%d", &idx, &L, &R);
				// assert(idx <= cnt && 1 <= L && L <= R && R <= pool[root[idx]].size);
				root[++cnt] = Segment(root[idx], L, R);
				scanf("%d%d%d", &idx, &L, &R);
				// assert(idx < cnt && 1 <= L && L <= R && R <= pool[root[idx]].size);
				root[cnt] = Merge(root[cnt], Segment(root[idx], L, R));
				// assert(pool[root[cnt]].size <= 1000000);
			} else {
				int idx, m;
				scanf("%d%d", &idx, &m);
				// assert(idx <= cnt && (sum_k += m) <= 1000000);
				int rt = root[idx];
				n = min(pool[rt].size, m);
				// assert(m <= (n * (n + 1)) >> 1);
				priority_queue<pair<long long, int> > Q;
				stp = tot;
				for(int i = 0; i < n; ++i) {
					int val = pool[rt].min, idx;
					rt = EraseMin(rt, idx);
					Q.push(make_pair(-val, idx));
				}
				tot = stp;
				rt = root[idx];
				for(int i = 0; i < m; ++i) {
					// assert(!Q.empty());
					pair<long long, int> cur = Q.top();
					Q.pop();
					// assert(-cur.first <= (long long)1e18);
					printf("%lld\n", -cur.first);
					if(cur.second + 1 <= pool[rt].size)
						Q.push(make_pair(cur.first - GetVal(rt, cur.second + 1), cur.second + 1));
				}
			}
		}
	}
	return 0;
}
