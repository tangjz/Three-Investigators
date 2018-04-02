#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100010, maxp = maxn * 20;
int tot, tt;
int fa[maxn][18];
int ls[maxp], rs[maxp];
ll sum[maxp];
int n, m;
int c[maxn];
int q[maxn];
int rt[maxn];
int dep[maxn];
vector<int> g[maxn];

int insert(int rt, int l, int r, int x){
	int t = ++tot; ls[t] = ls[rt], rs[t] = rs[rt], sum[t] = sum[rt];
	if(l == r){
		sum[t] += q[x];
		return t;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) ls[t] = insert(ls[rt], l, mid, x);
	else rs[t] = insert(rs[rt], mid + 1, r, x);
	sum[t] = sum[ls[t]] + sum[rs[t]];
	return t;
}

ll ask(int t, int l, int r, int x, int y){
	if(!t) return 0;
	if(x <= l && y >= r) return sum[t];
	int mid = (l + r) >> 1;
	if(y <= mid) return ask(ls[t], l, mid, x, y);
	if(x > mid) return ask(rs[t], mid + 1, r, x, y);
	return ask(ls[t], l, mid, x, y) + ask(rs[t], mid + 1, r, x, y);
}

void dfs(int t){
	c[t] = lower_bound(q + 1, q + tt + 1, c[t]) - q;
	rt[t] = insert(rt[fa[t][0]], 1, tt, c[t]);
	dep[t] = dep[fa[t][0]] + 1;
	for(int i = 1; fa[t][i - 1]; ++i)
		fa[t][i] = fa[fa[t][i - 1]][i - 1];
	for(int v : g[t]){
		if(v == fa[t][0]) continue;
		memset(fa[v], 0, sizeof(fa[v]));
		fa[v][0] = t;
		dfs(v);
	}
}

int lca(int u, int v){
	if(dep[u] > dep[v]) swap(u, v);
	for(int i = 16; i >= 0; --i)
		if(dep[fa[v][i]] >= dep[u]) v = fa[v][i];
	if(u == v) return u;
	for(int i = 16; i >= 0; --i)
		if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

int main(){
	while(~scanf("%d%d", &n, &m)){
		tot = 0;
		for(int i = 1; i <= n; ++i) scanf("%d", c + i), q[i] = c[i], g[i].clear();
		sort(q + 1, q + n + 1);
		tt = unique(q + 1, q + n + 1) - q - 1;
		for(int i = 1; i < n; ++i){
			static int x, y;
			scanf("%d%d", &x, &y);
			g[x].pb(y);
			g[y].pb(x);
		}
		dfs(1);
		while(m--){
			static int s, t, a, b;
			scanf("%d%d%d%d", &s, &t, &a, &b);
			int g = lca(s, t);
			a = lower_bound(q + 1, q + tt + 1, a) - q;
			b = upper_bound(q + 1, q + tt + 1, b) - q - 1;
			ll res = a <= b ? ask(rt[s], 1, tt, a, b) + ask(rt[t], 1, tt, a, b) - 2 * ask(rt[g], 1, tt, a, b) + (c[g] >= a && c[g] <= b ? q[c[g]] : 0) : 0;
			printf("%lld%c", res, " \n"[m == 0]);
		}

	}
	return 0;
}
