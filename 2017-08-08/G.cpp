#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 998244353
#define all(a) a.begin(), a.end()

const int maxn = 50010, maxm = 210;
int T;
int n, m;
int f[maxn][maxm], g[maxn][maxm];
int ff[maxm], gg[maxm];
int sz[maxn];
int tot, to[maxn * 2], he[maxn], ne[maxn * 2], e;

void dfs(int t, int fa){
	f[t][0] = 1, g[t][0] = 0;
	f[t][1] = g[t][1] = 0;
	sz[t] = 1;
	for(int j = he[t]; j; j = ne[j]){
		int v = to[j];
		if(v == fa) continue;
		dfs(v, t);
		memset(ff, 0, sizeof(int) * min(m, sz[t] + sz[v] + 1));
		memset(gg, 0, sizeof(int) * min(m, sz[t] + sz[v] + 1));
		for(int i = min(m - 1, sz[t]); i >= 0; --i)
			for(int j = min(m - 1, sz[v]); j >= 0; --j){
				int x = (i + j) % m, y = (x + 1) % m;
				ff[x] = (ff[x] + (ll)f[t][i] * f[v][j] + 2LL * f[t][i] * g[v][j]) % M;
				gg[y] = (gg[y] + (ll)f[t][i] * f[v][j]) % M;
				gg[x] = (gg[x] + 2LL * g[t][i] * (f[v][j] + g[v][j])) % M;
			}
		sz[t] += sz[v];
		memcpy(f[t], ff, sizeof(int) * min(m, sz[t] + 1));
		memcpy(g[t], gg, sizeof(int) * min(m, sz[t] + 1));
	}
}

int main(){
	int T;
	freopen("input.txt", "r", stdin);
	freopen("1007.out", "w", stdout);
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		e = 0;
		memset(he, 0, sizeof(int) * (n + 1));
		for(int i = 1; i < n; ++i){
			static int u, v;
			scanf("%d%d", &u, &v);
			to[++e] = v, ne[e] = he[u], he[u] = e;
			to[++e] = u, ne[e] = he[v], he[v] = e;
		}
		dfs(1, 0);
		printf("%d\n", (f[1][0] + g[1][0]) % M);
	}
	return 0;
}
