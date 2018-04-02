#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 1010;
int tim, tot, top;
int sta[maxn], dfn[maxn], low[maxn], col[maxn];
vector<int> g[maxn], f[maxn];
int du[maxn];
bool ins[maxn];
int n, m, T;

void dfs(int t){
	sta[++top] = t, ins[t] = 1;
	dfn[t] = low[t] = ++tim;
	for(int v : g[t])
		if(!dfn[v]){
			dfs(v);
			low[t] = min(low[t], low[v]);
		}else if(ins[v]) low[t] = min(low[t], dfn[v]);
	
	if(dfn[t] == low[t]){
		col[t] = ++tot; ins[t] = 0;
		while(sta[top] != t) col[sta[top]] = tot, ins[sta[top--]] = 0;
		top--;
	}
}

bool solve(){
	for(int i = 1; i <= tot; ++i) f[i].clear();
	memset(du, 0, sizeof(du));
	for(int i = 1; i <= n; ++i)
		for(int v : g[i])
			if(col[i] != col[v])
				f[col[i]].pb(col[v]), ++du[col[v]];
	int now = -1;
	for(int i = 1; i <= tot; ++i)
		if(du[i] == 0){
			if(now == -1) now = i;
			else return 0;
		}
	for(int i = 1; i <= tot; ++i){
		int t = now; now = -1;
		for(int v : f[t]){
			--du[v];
			if(du[v] == 0){
				if(now == -1) now = v;
				else return 0;
			}
		}
	}
	return 1;
}

int main(){
	scanf("%d", &T);
	while(T--){
		tot = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) g[i].clear();
		for(int i = 1; i <= m; ++i){
			static int u, v;
			scanf("%d%d", &u, &v);
			g[u].pb(v);
		}
		memset(dfn, 0, sizeof(dfn));
		memset(ins, 0, sizeof(ins));
		tim = 0;
		top = 0;
		for(int i = 1; i <= n; ++i)
			if(!dfn[i]) dfs(i);
		if(solve()) puts("I love you my love and our love save us!");
		else puts("Light my fire!");
	}
	return 0;
}
