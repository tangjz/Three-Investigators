#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100005;
int n, m;
vector<int> two[maxn], one[maxn], g[maxn], po[maxn];
int du[maxn];
int t1[maxn], t2[maxn];
int fa[maxn];
bool flag = 1;

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void merge(int u, int v){
	u = find(u), v = find(v);
	if(u == v) flag = 0;
	fa[u] = v;
}

void dfs(int u, int fa){
	for(int v : two[u]){
		if(v == fa) continue;
		dfs(v, u);
		if(t1[v] + 1 > t1[u]) t2[u] = t1[u], t1[u] = t1[v] + 1;
		else t2[u] = max(t2[u], t1[v] + 1);
	}
}

void dfs2(int u, int fa){
	for(int v : two[u]){
		if(v == fa) continue;		
		int len = t1[v] + 1 == t1[u] ? t2[u] + 1 : t1[u] + 1;
		if(len > t1[v]) t2[v] = t1[v], t1[v] = len;
		else t2[v] = max(t2[v], len);
		dfs2(v, u);
	}
}

void solve(){
	for(int i = 1; i <= n; ++i)
		for(int v : one[i]){
			if(find(i) == find(v)) flag = 0;
			g[find(i)].pb(find(v));
			++du[find(v)];
			po[find(i)].pb(i);
		}
	if(!flag) return (void)puts("Infinite");

	int que[maxn], l = 1, r = 0, tot = 0;
	for(int i = 1; i <= n; ++i)
		if(i == find(i)){
			if(!du[i]) que[++r] = i;
			++tot;
		}
	while(l <= r){
		int t = que[l++];
		for(int v : g[t])
			if(!(--du[v])) que[++r] = v;
	}
	if(tot != r) return (void)puts("Infinite");
	
	for(int i = 1; i <= r; ++i){
		int t = que[i];
		dfs(t, 0);
		dfs2(t, 0);
		for(int u : po[t])
			for(int v : one[u])
				if(t1[u] + 1 > t1[v]) t2[v] = t1[v], t1[v] = t1[u] + 1;
				else t2[v] = max(t2[v], t1[u] + 1);
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i)
		ans = max(ans, t1[i]);
	printf("%d\n", ans);
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1, u, v, w; i <= m; ++i){
		scanf("%d%d%d", &u, &v, &w);
		if(w == 2) merge(u, v), two[u].pb(v), two[v].pb(u);
		else one[u].pb(v);
	}
	solve();	
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
