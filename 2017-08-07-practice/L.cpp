#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 5010;
int Test, n, m;
vector<int> g[maxn];
int sta[maxn], top;
bool ins[maxn];
int col[maxn], tot;
int dfn[maxn], low[maxn], tim;
vector<int> ed[maxn];
int p[maxn], vis[maxn], idx;

void dfs(int t){
	sta[++top] = t; ins[t] = 1;
	dfn[t] = low[t] = ++tim;
	for(int v : g[t]){
		if(!dfn[v]){
			dfs(v);
			low[t] = min(low[t], low[v]);
		}else if(ins[v]) low[t] = min(low[t], dfn[v]);
	}
	if(dfn[t] == low[t]){
		col[t] = ++tot; ins[t] = 0;
		while(sta[top] != t) col[sta[top]] = tot, ins[sta[top--]] = 0;
		top--;
	}
}

int ddfs(int t){
	for(int v : ed[t])
		if(vis[v] < idx){
			vis[v] = idx;
			if(!p[v] || ddfs(p[v])){
				p[v] = t;
				return 1;
			}
		}
	return 0;
}

int main(){
	scanf("%d", &Test);
	while(Test--){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) g[i].clear();
		for(int i = 0; i < m; ++i){
			static int u, v;
			scanf("%d%d", &u, &v);
			g[u].pb(v);
		}
		memset(dfn, 0, sizeof(int) * (n + 1));
		tim = tot = 0;
		for(int i = 1; i <= n; ++i)
			if(!dfn[i]) dfs(i);
		for(int i = 1; i <= tot; ++i) ed[i].clear();
		for(int i = 1; i <= n; ++i)
			for(int v : g[i])
				if(col[i] != col[v])
					ed[col[i]].pb(col[v]);

		for(int i = 1; i <= tot; ++i)
			ed[i].erase(unique(all(ed[i])), ed[i].end());
		
		memset(p, 0, sizeof(int) * (tot + 1));
		int res = tot;
		for(int i = 1; i <= tot; ++i){
			++idx;
			if(ddfs(i)) --res;
		}
		
		printf("%d\n", res);
	}

	return 0;
}
