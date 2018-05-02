#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int n, P, Q, tot, a[maxn], sz[maxn], dis[maxn], ord[maxn];
vector<pair<int, int> > e[maxn];
bool ban[maxn], vis[maxn];
void dfs(int u) {
	ord[tot++] = u;
	vis[u] = 1;
	sz[u] = 1;
	for(auto it : e[u]) {
		int v = it.first;
		if(vis[v])
			continue;
		dis[v] = dis[u] + it.second;
		dfs(v);
		sz[u] += sz[v];
	}
}
int findRoot(int u) {
	tot = 0;
	memcpy(vis + 1, ban + 1, n * sizeof(bool));
	dfs(u);
	int rt = u, cnt = tot - 1;
	memcpy(vis + 1, ban + 1, n * sizeof(bool));
	for(int i = 0; i < tot; ++i) {
		int u = ord[i], mx = 0;
		vis[u] = 1;
		for(auto it : e[u]) {
			int v = it.first;
			if(vis[v])
				continue;
			mx = max(mx, sz[v]);
		}
		mx = max(mx, tot - sz[u]);
		if(mx < cnt) {
			rt = u;
			cnt = mx;
		}
	}
	return rt;
}
LL solve(int u, int adt) {
	tot = 0;
	dis[u] = adt;
	dfs(u);
	sort(ord, ord + tot, [&](int const &u, int const &v) {
		return dis[u] > dis[v];
	});
	LL ret = 0, cnt = 0;
	for(int i = 0; i < tot; ++i) {
		cnt += a[ord[i]];
		ret = max(ret, (cnt - 1) / P + (LL)Q * dis[ord[i]]);
	}
	return ret;
}
int main() {
	scanf("%d%d%d", &n, &P, &Q);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i < n; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
	}
	if(n == 1) {
		puts("1");
		return 0;
	}
	int rem = n, rt = 1;
	while(rem > 2) {
		rt = findRoot(rt);
		int sp = -1;
		LL mx = -1;
		memset(vis + 1, 0, n * sizeof(bool));
		vis[rt] = 1;
		for(auto it : e[rt]) {
			int v = it.first;
			if(ban[v])
				continue;
			LL val = solve(v, it.second);
			if(mx < val) {
				mx = val;
				sp = v;
			}
		}
		memcpy(vis + 1, ban + 1, n * sizeof(bool));
		vis[rt] = 1;
		for(auto it : e[rt]) {
			int v = it.first;
			if(v == sp)
				continue;
			tot = 0;
			dfs(v);
			for(int i = 0; i < tot; ++i, --rem)
				ban[ord[i]] = 1;
		}
	}
	int tr = -1, dt = -1;
	for(auto it : e[rt]) {
		int v = it.first;
		if(!ban[v]) {
			tr = it.first;
			dt = it.second;
			break;
		}
	}
	memset(vis + 1, 0, n * sizeof(bool));
	vis[tr] = 1;
	LL lft = solve(rt, dt);
	vis[tr] = 0;
	LL rht = solve(tr, dt), res = rht - lft + (LL)Q * dt;
	if(res <= 0) {
		printf("%d\n", rt);
	} else if(res >= 2LL * Q * dt) {
		printf("%d\n", tr);
	} else {
		printf("%d %d %.20f\n", rt, tr, (double)res / (Q << 1));
	}
	return 0;
}
