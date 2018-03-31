#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 500001;
int n, tot, lnk1[maxn], lnk2[maxn], lst[maxn], dsu[maxn], seq1[maxn], seq2[maxn], ans[maxn];
struct Edge {
	int nxt, v;
} e[maxn << 2 | 1];
struct NewEdge {
	int nxt, v, eid;
} g[maxn << 1 | 1];
inline int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
inline void dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return;
	if(dsu[u] < dsu[v])
		std::swap(u, v);
	if(dsu[u] == dsu[v])
		--dsu[v];
	dsu[u] = v;
}
void dfs(int u, int fa) {
	int pre = -1;
	for(int it = lst[u]; it != -1; it = g[it].nxt)
		if(g[it].v != fa)
			dfs(g[it].v, u);
		else
			pre = it;
	if(pre == -1)
		return;
	if(ans[u] == -1)
		ans[u] = g[pre].eid;
	else {
		int it = g[pre].eid, jt = ans[u];
		printf("%d %d %d %d\n", e[it].v, e[it ^ 1].v, e[jt].v, e[jt ^ 1].v);
	}
}
inline bool cmp(int const &x, int const &y) {
	return e[x].v < e[y].v;
}
int main() {
	scanf("%d", &n);
	memset(lnk1 + 1, -1, n * sizeof(int));
	memset(lnk2 + 1, -1, n * sizeof(int));
	memset(dsu + 1, -1, n * sizeof(int));
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[tot] = (Edge){lnk1[u], v};
		lnk1[u] = tot++;
		e[tot] = (Edge){lnk1[v], u};
		lnk1[v] = tot++;
	}
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[tot] = (Edge){lnk2[u], v};
		lnk2[u] = tot++;
		e[tot] = (Edge){lnk2[v], u};
		lnk2[v] = tot++;
	}
	tot = (n - 1) << 1;
	for(int i = 1; i <= n; ++i) {
		int sz1 = 0, sz2 = 0;
		for(int &it = lnk1[i]; it != -1; it = e[it].nxt)
			seq1[sz1++] = it;
		for(int &it = lnk2[i]; it != -1; it = e[it].nxt)
			seq2[sz2++] = it;
		std::sort(seq1, seq1 + sz1, cmp);
		std::sort(seq2, seq2 + sz2, cmp);
		int j = 0, k = 0;
		while(j < sz1 && k < sz2)
			if(e[seq1[j]].v < e[seq2[k]].v) {
				e[seq1[j]].nxt = lnk1[i];
				lnk1[i] = seq1[j++];
			} else if(e[seq1[j]].v > e[seq2[k]].v) {
				e[seq2[k]].nxt = lnk2[i];
				lnk2[i] = seq2[k++];
			} else {
				--tot;
				dsu_merge(i, e[seq1[j]].v);
				++j;
				++k;
			}
		while(j < sz1) {
			e[seq1[j]].nxt = lnk1[i];
			lnk1[i] = seq1[j++];
		}
		while(k < sz2) {
			e[seq2[k]].nxt = lnk2[i];
			lnk2[i] = seq2[k++];
		}
	}
	printf("%d\n", tot >> 1);
	tot = 0;
	memset(lst + 1, -1, n * sizeof(int));
	for(int i = 1; i <= n; ++i) {
		int u = dsu_find(i);
		for(int it = lnk2[i]; it != -1; it = e[it].nxt) {
			int v = dsu_find(e[it].v);
			if(u != v) {
				g[tot] = (NewEdge){lst[u], v, it};
				lst[u] = tot++;
			}
		}
	}
	memset(ans + 1, -1, n * sizeof(int));
	dfs(dsu_find(1), -1);
	tot = 0;
	memset(lst + 1, -1, n * sizeof(int));
	for(int i = 1; i <= n; ++i) {
		int u = dsu_find(i);
		for(int it = lnk1[i]; it != -1; it = e[it].nxt) {
			int v = dsu_find(e[it].v);
			if(u != v) {
				g[tot] = (NewEdge){lst[u], v, it};
				lst[u] = tot++;
			}
		}
	}
	dfs(dsu_find(1), -1);
	return 0;
}
