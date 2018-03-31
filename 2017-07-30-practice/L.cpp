#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001, maxm = 160001, maxs = 1800001;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
	bool operator < (Point const &t) const {
		return x < t.x || (x == t.x && y < t.y);
	}
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y};
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	LL dot(Point const &t) const {
		return (LL)x * t.x + (LL)y * t.y;
	}
	LL det(Point const &t) const {
		return (LL)x * t.y - (LL)y * t.x;
	}
} p[maxn];
inline int polar_cmp(Point const &a, Point const &b) {
	if(!a.y && !b.y && (LL)a.x * b.x <= 0)
		return a.x > b.x;
	if(!a.y && a.x >= 0 && b.y)
		return 1;
	if(!b.y && b.x >= 0 && a.y)
		return 0;
	if((LL)a.y * b.y <= 0)
		return a.y > b.y;
	LL tmp = a.det(b);
	return tmp > 0 || (!tmp && a.x < b.x);
}
int t, n, m, seq[maxn], ord[maxn], tmp[maxn], pool[maxs], *stk;
vector<int> ans[maxm];
int lnk[maxn], dep[maxn], fa[maxn], sz[maxn], son[maxn], top[maxn], idx[maxn];
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1];
void tree_build(int rt) {
	int L = 1, R = 0;
	dep[rt] = fa[rt] = 0;
	ord[++R] = rt;
	while(L <= R) {
		int u = ord[L++];
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u])
				continue;
			dep[v] = dep[u] + 1;
			fa[v] = u;
			ord[++R] = v;
		}
	}
	memset(sz + 1, 0, n * sizeof(int));
	memset(son + 1, 0, n * sizeof(int));
	++sz[rt];
	for(int i = n; i > 1; --i) {
		int u = ord[i], p = fa[u];
		sz[p] += (++sz[u]);
		if(sz[son[p]] < sz[u])
			son[p] = u;
	}
	top[rt] = idx[rt] = 1;
	for(int i = 1; i <= n; ++i) {
		int u = ord[i], id = idx[u];
		seq[id++] = u;
		if(sz[u] == 1)
			continue;
		top[son[u]] = top[u];
		idx[son[u]] = id;
		id += sz[son[u]];
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || v == son[u])
				continue;
			top[v] = v;
			idx[v] = id;
			id += sz[v];
		}
	}
}
struct Query {
	int u, v;
	Point p;
	vector<int> *res;
	void init(vector<int> &_res) {
		scanf("%d%d", &u, &v);
		p.read();
		res = &_res;
	}
	bool operator < (Query const &t) const {
		return polar_cmp(p, t.p);
	}
} query[maxm];
struct Segment {
	int *sta, *pos, *end;
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_build(int L, int R) {
	if(L < R) {
		int M = (L + R) >> 1, cnt = 0;
		seg_build(L, M);
		seg_build(M + 1, R);
		for(int i = L, j = M + 1; i <= M || j <= R; )
			if(j > R || (i <= M && p[ord[i]] < p[ord[j]]))
				tmp[cnt++] = ord[i++];
			else
				tmp[cnt++] = ord[j++];
		memcpy(ord + L, tmp, cnt * sizeof(int));
	}
	int cnt = 0;
	for(int i = L; i <= R; ++i) {
		for( ; cnt > 1 && (p[stk[cnt - 1]] - p[stk[cnt - 2]]).det(p[ord[i]] - p[stk[cnt - 2]]) < 0; --cnt);
		stk[cnt++] = ord[i];
	}
	seg[seg_idx(L, R)] = (Segment){stk, stk, stk + cnt};
	stk += cnt;
}
void seg_que(int L, int R, int l, int r, LL &dis, Point &dir) {
	if(l <= L && R <= r) {
		Segment &cur = seg[seg_idx(L, R)];
		LL pdis = INF, cdis;
		for( ; cur.pos != cur.end; ++cur.pos) {
			cdis = dir.dot(p[*cur.pos]);
			if(pdis < cdis)
				break;
			pdis = cdis;
		}
		if(pdis != INF) {
			--cur.pos;
			if(pdis < dis)
				dis = pdis;
		}
		return;
	}
	int M = (L + R) >> 1;
	if(l <= M)
		seg_que(L, M, l, r, dis, dir);
	if(M < r)
		seg_que(M + 1, R, l, r, dis, dir);
}
void seg_que(int L, int R, int l, int r, LL dis, Point &dir, vector<int> *out) {
	if(l <= L && R <= r) {
		Segment &cur = seg[seg_idx(L, R)];
		if(cur.pos != cur.end && dir.dot(p[*cur.pos]) == dis) {
			int *ptr = cur.pos, *stp = cur.sta - 1;
			for( ; ptr != stp && dir.dot(p[*ptr]) == dis; --ptr)
				out -> push_back(*ptr);
		}
		return;
	}
	int M = (L + R) >> 1;
	if(l <= M)
		seg_que(L, M, l, r, dis, dir, out);
	if(M < r)
		seg_que(M + 1, R, l, r, dis, dir, out);
}
void solve() {
	stk = pool;
	memcpy(ord + 1, seq + 1, n * sizeof(int));
	seg_build(1, n);
	sort(query + 1, query + m + 1);
	for(int i = 1; i <= m; ++i) {
		Query &cur = query[i];
		if(cur.p.y < 0 || (!cur.p.y && cur.p.x > 0))
			continue;
		LL dis = INF;
		int u = cur.u, v = cur.v;
		for(int pu = top[u], pv = top[v]; pu != pv; u = fa[pu], pu = top[u]) {
			if(dep[pu] < dep[pv]) {
				swap(u, v);
				swap(pu, pv);
			}
			seg_que(1, n, idx[pu], idx[u], dis, cur.p);
		}
		if(dep[u] > dep[v])
			swap(u, v);
		seg_que(1, n, idx[u], idx[v], dis, cur.p);
		u = cur.u;
		v = cur.v;
		for(int pu = top[u], pv = top[v]; pu != pv; u = fa[pu], pu = top[u]) {
			if(dep[pu] < dep[pv]) {
				swap(u, v);
				swap(pu, pv);
			}
			seg_que(1, n, idx[pu], idx[u], dis, cur.p, cur.res);
		}
		if(dep[u] > dep[v])
			swap(u, v);
		seg_que(1, n, idx[u], idx[v], dis, cur.p, cur.res);
	}
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			p[i].read();
		memset(lnk + 1, -1, n * sizeof(int));
		for(int i = 0; i < n - 1; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[i << 1] = (Edge){lnk[u], v};
			lnk[u] = i << 1;
			e[i << 1 | 1] = (Edge){lnk[v], u};
			lnk[v] = i << 1 | 1;
		}
		tree_build(1);
		scanf("%d", &m);
		for(int i = 1; i <= m; ++i) {
			vector<int>().swap(ans[i]);
			query[i].init(ans[i]);
		}
		solve();
		for(int i = 1; i <= n; ++i) {
			p[i].x = -p[i].x;
			p[i].y = -p[i].y;
		}
		for(int i = 1; i <= m; ++i) {
			query[i].p.x = -query[i].p.x;
			query[i].p.y = -query[i].p.y;
		}	
		solve();
		printf("Case %d:\n", Case);
		for(int i = 1; i <= m; ++i) {
			sort(ans[i].begin(), ans[i].end());
			for(int j = 0, sz = (int)ans[i].size(); j < sz; ++j)
				printf("%d%c", ans[i][j], " \n"[j == sz - 1]);
		}
	}
	return 0;
}
