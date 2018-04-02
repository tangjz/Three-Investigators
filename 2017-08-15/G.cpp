#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 55 * 55, maxe = 1000000, oo = 1e9;
int e = 1, inx, vis[maxn], ln[maxn], ht[maxn], l, r, S, T;
int to[maxe], ne[maxe], he[maxn], cap[maxe];

int n, m, k;
int p[55][55];

void link(int x, int y, int v){
	to[++e] = y, ne[e] = he[x], he[x] = e, cap[e] = 0;
	to[++e] = x, ne[e] = he[y], he[y] = e, cap[e] = v;
}

bool bfs(){
	for(ln[l = r = 1] = S, vis[S] = ++inx, ht[S] = 1; l <= r; ++l)
		for(int j = he[ln[l]]; j; j = ne[j])
			if(vis[to[j]] < inx && cap[j ^ 1]){
				vis[to[j]] = inx, ht[to[j]] = ht[ln[l]] + 1, ln[++r] = to[j];
				if(to[j] == T) return 1;
			}
	return 0;
}

int dfs(int f, int d){
	if(!f || d == S) return f;
	int flow = 0, k;
	for(int j = he[d]; j; j = ne[j])
		if(vis[to[j]] == inx && ht[to[j]] == ht[d] - 1 && (k = dfs(min(f, cap[j]), to[j]))){
			f -= k, flow += k;
			cap[j] -= k, cap[j ^ 1] += k;
			if(!f) return flow;
		}
	ht[d] = maxn + 1;
	return flow;
}

ll dinic(){
	ll maxflow = 0;
	while(bfs()) maxflow += dfs(oo, T);
	return maxflow;
}

void init(){
	memset(he, 0, sizeof(he));
	e = 1;
}

int main(){
	int Test;
	scanf("%d", &Test);
	while(Test--){
		scanf("%d%d%d", &n, &m, &k);
		init();
		int tot = 1;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m + 1; ++j)
				p[i][j] = ++tot;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j){
				static int w;
				scanf("%d", &w);
				link(p[i][j], p[i][j + 1], 1000 - w);
			}
		for(int i = 1; i <= k; ++i){
			static int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			for(int j = 1; j <= m + 1; ++j)
				if(j - z >= 1 && j - z <= m + 1)
					link(p[x][j], p[y][j - z], oo);
		}
		S = tot + 1, T = S + 1;
		for(int i = 1; i <= n; ++i)
			link(S, p[i][1], oo), link(p[i][m + 1], T, oo);
		ll res = n * 1000 - dinic();
		printf("%lld\n", res < 0 ? -1 : res);
	}

	return 0;
}
