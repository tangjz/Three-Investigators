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
const int maxp = maxn * 18;
int son[maxp][2], cnt[maxp];
int a[maxn], fa[maxn][18], dep[maxn], rt[maxn];
int tot;
vector<int> g[maxn];
int n, m;

void insert(int &t, int dp, int v, int pre_t){
	t = ++tot;
	son[t][0] = son[pre_t][0];
	son[t][1] = son[pre_t][1];
	cnt[t] = cnt[pre_t] + 1;
	
	if(dp < 0) return;
	bool x = v >> dp & 1;
	insert(son[t][x], dp - 1, v, son[pre_t][x]);
}

void build(int t){
	insert(rt[t], 15, a[t], rt[fa[t][0]]);
	dep[t] = dep[fa[t][0]] + 1;
	for(int i = 1; fa[t][i - 1]; ++i)
		fa[t][i] = fa[fa[t][i - 1]][i - 1];
	for(int v : g[t]){
		if(v == fa[t][0]) continue;
		memset(fa[v], 0, sizeof(fa[v]));
		fa[v][0] = t;
		build(v);
	}
}

int lca(int u, int v){
	if(dep[u] > dep[v]) swap(u, v);
	for(int i = 16, dist = dep[v] - dep[u]; i >= 0; --i)
		if(dist >> i & 1) v = fa[v][i];
	if(u == v) return u;
	for(int i = 16; i >= 0; --i)
		if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

int query(int dp, int t1, int t2, int t3, int v){
	if(dp < 0) return 0;
	bool x = v >> dp & 1;
	int tmp = cnt[son[t1][x ^ 1]] + cnt[son[t2][x ^ 1]] - 2 * cnt[son[t3][x ^ 1]];
	if(tmp) return 1 << dp | query(dp - 1, son[t1][x ^ 1], son[t2][x ^ 1], son[t3][x ^ 1], v);
	else return query(dp - 1, son[t1][x], son[t2][x], son[t3][x], v);
}

int main(){
	while(~scanf("%d%d", &n, &m)){
		for(int i = 1; i <= n; ++i) scanf("%d", a + i), rt[i] = 0, g[i].clear();
		for(int i = 1; i < n; ++i){
			static int u, v;
			scanf("%d%d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		tot = 0;
		build(1);
		while(m--){
			static int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			int g = lca(x, y);
			printf("%d\n", max(a[g] ^ z, query(15, rt[x], rt[y], rt[g], z)));
		}
	}

	return 0;
}
