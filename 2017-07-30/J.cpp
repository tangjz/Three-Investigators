#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100;
int T, n, m;
int fa[maxn][20];
int sz[maxn], dep[maxn];
vector<int> g[maxn];

void dfs(int t){
	dep[t] = dep[fa[t][0]] + 1;
	for(int i = 1; fa[t][i - 1]; ++i)
		fa[t][i] = fa[fa[t][i - 1]][i - 1];
	sz[t] = 1;
	for(auto v : g[t]){
		if(v == fa[t][0]) continue;
		memset(fa[v], 0, sizeof(fa[v]));
		fa[v][0] = t;
		dfs(v);
		sz[t] += sz[v];
	}
}

int lca(int u, int v){
	if(dep[u] > dep[v]) swap(u, v);
	for(int i = 17; i >= 0; --i)
		if(dep[fa[v][i]] >= dep[u]) v = fa[v][i];
	if(u == v) return v;
	for(int i = 17; i >= 0; --i)
		if(fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

inline int get_len(int x, int y, int p){
	return dep[x] + dep[y] - 2 * dep[p];
}

pair<int, int> get_mid(int x, int y, int p){
	int len = get_len(x, y, p);
	int d = dep[x] >= dep[y] ? (len - 1) / 2 : len / 2;
	int u = dep[x] >= dep[y] ? x : y, v = u;
	for(int i = 17; i >= 0; --i)
		if(d >> i & 1) u = fa[u][i];
	return mkp(v == x ? fa[u][0] : u, v == x ? n - sz[u] : sz[u]);
}

int work(int x, int y, int z){
	int p1 = lca(x, y), p2 = lca(x, z);
	auto d1 = get_mid(x, y, p1), d2 = get_mid(x, z, p2);
	int x1 = (get_len(x, y, p1) + 1) / 2, x2 = (get_len(x, z, p2) + 1) / 2;
	int x3 = get_len(d1.fi, d2.fi, lca(d1.fi, d2.fi));
	int res = n - d1.se - d2.se;
	if(x1 + x3 == x2) res += d2.se;
	else if(x2 + x3 == x1) res += d1.se;
	return res;
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) g[i].clear();
		for(int i = 1; i < n; ++i){
			static int u, v;
			scanf("%d%d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		dfs(1);
		scanf("%d", &m);
		while(m--){
			static int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			printf("%d %d %d\n", work(x, y, z), work(y, x, z), work(z, x, y));
		}
	}
	
	return 0;
}
