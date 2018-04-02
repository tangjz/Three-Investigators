#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 300100;
int n, k;
int p[maxn];
vector<int> g[maxn];
int dep[maxn], fa[maxn][20];
int rmq[maxn][20];
pair<pair<int, int>, int> sta[maxn];
int LOG[maxn];
ll f[2][maxn];

void dfs(int t){
	dep[t] = dep[fa[t][0]] + 1;
	for(int i = 1; fa[t][i - 1]; ++i)
		fa[t][i] = fa[fa[t][i - 1]][i - 1];
	for(auto v : g[t]){
		if(v == fa[t][0]) continue;
		memset(fa[v], 0, sizeof(fa[v]));
		fa[v][0] = t;
		dfs(v);
	}
}

int lca(int u, int v){
	if(dep[u] > dep[v]) swap(u, v);
	for(int i = 18; i >= 0; --i)
		if(dep[fa[v][i]] >= dep[u]) v = fa[v][i];
	if(u == v) return u;
	for(int i = 18; i >= 0; --i)
		if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

void build_rmq(){
	for(int i = 0; i <= 18; ++i) LOG[1 << i] = i;
	for(int i = 1; i <= n; ++i) LOG[i] = max(LOG[i - 1], LOG[i]);

	for(int i = 1; i <= n; ++i) rmq[i][0] = p[i];
	for(int j = 1; j <= 18; ++j)
		for(int i = 1; i + (1 << j) - 1 <= n; ++i)
			rmq[i][j] = lca(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);
}

inline int calc(int l, int r){
	int k = LOG[r - l + 1];
	return lca(rmq[l][k], rmq[r - (1 << k) + 1][k]);
}

inline int calc(int pre, int l, int r){
	return f[pre][l] + dep[calc(l + 1, r)];
}

int main(){
	while(~scanf("%d%d", &n, &k)){
		for(int i = 1; i <= n; ++i) scanf("%d", p + i), g[i].clear();
		for(int i = 1; i < n; ++i){
			static int u, v;
			scanf("%d%d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		dfs(1);
		build_rmq();
		
		memset(f, 127, sizeof(f));
		f[0][0] = 0;
		int pre = 0, now = 1;
		for(int i = 1; i <= k; ++i){
			memset(f[now], 127, sizeof(int) * (n + 1));
			sta[1] = mkp(mkp(1, n), 0);
			int l = 1, r = 1;
			for(int j = 1; j <= n; ++j){
				f[now][j] = calc(pre, sta[l].se, j);
				if(sta[l].fi.fi == j) sta[l].fi.fi++;
				if(sta[l].fi.fi > sta[l].fi.se) ++l;
				if(j == n) continue;
				if(l > r){
					sta[++r] = mkp(mkp(j + 1, n), j);
					continue;
				}
				if(calc(pre, j, n) >= calc(pre, sta[r].se, n)) continue;
				while(l <= r && calc(pre, sta[r].se, sta[r].fi.fi) >= calc(pre, j, sta[r].fi.fi)) --r;
				if(l > r) sta[++r] = mkp(mkp(j + 1, n), j);
				else{
					int lt = sta[r].fi.fi, rt = sta[r].fi.se + 1;
					while(lt + 1 < rt){
						int d = (lt + rt) >> 1;
						if(calc(pre, sta[r].se, d) < calc(pre, j, d)) lt = d;
						else rt = d;
					}
					sta[r].fi.se = lt;
					sta[++r] = mkp(mkp(rt, n) ,j);
				}
			}
			swap(pre, now);
		}
		printf("%lld\n", f[pre][n]);
	}

	return 0;
}
