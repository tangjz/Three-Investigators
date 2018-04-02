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
int tot, root, last, par[maxn * 2], go[maxn * 2][26], val[maxn * 2];
vector<int> g[maxn * 2];
bitset<100> tagx[maxn * 2], tagy[maxn * 2];
bool mark[maxn * 2];
int n, m;
char s[maxn];
int wp[maxn];
int ed[maxn];
int ans[110];

void init(int p){
	g[p].clear();
	tagx[p].reset(), tagy[p].reset();
	mark[p] = 0;
	memset(go[p], 0, sizeof(go[p]));
}

void extend(int w){
	int p = last, np;
	if(!go[p][w]){
		np = ++tot; val[np] = val[p] + 1; init(tot);
		while(p && !go[p][w]) go[p][w] = np, p = par[p];
		if(!p) par[np] = root;
		else{
			int q = go[p][w];
			if(val[p] + 1 == val[q]) par[np] = q;
			else{
				int nq = ++tot; val[nq] = val[p] + 1; init(tot);
				memcpy(go[nq], go[q], sizeof(go[q]));
				par[nq] = par[q];
				par[q] = par[np] = nq;
				while(p && go[p][w] == q) go[p][w] = nq, p = par[p];
			}
		}
		last = np;
	}else{
		int q = go[p][w];
		if(val[p] + 1 == val[q]) last = q;
		else{
			int nq = ++tot; val[nq] = val[p] + 1; init(tot);
			memcpy(go[nq], go[q], sizeof(go[q]));
			par[nq] = par[q];
			par[q] = nq;
			while(p && go[p][w] == q) go[p][w] = nq, p = par[p];
			last = nq;
		}
	}
}

void dfs(int t){
	for(int v : g[t]){
		dfs(v);
		tagx[t] |= tagx[v];
		tagy[t] |= tagy[v];
	}
	if(mark[t]){
		for(int i = 0; i < m; ++i)
			if(tagx[t].test(i) && tagy[t].test(i))
				ans[i] = max(ans[i], val[t]);
	}
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);

		root=last=tot=1; init(1);
		for(int i = 1; i <= n; ++i){
			scanf("%s", s);
			last = 1;
			for(int j = 0; s[j]; ++j){
				extend(s[j] - 'a');
				wp[ed[i - 1] + j] = last;
				mark[last] = 1;	
			}
			ed[i] = ed[i - 1] + strlen(s);
		}
		for(int i = 2; i <= tot; ++i)
			g[par[i]].pb(i);
		scanf("%d", &m);
		memset(ans, 0, sizeof(ans));
		for(int i = 0; i < m; ++i){
			static int x, y;
			scanf("%d%d", &x, &y);
			for(int j = ed[x - 1]; j < ed[x]; ++j)
				tagx[wp[j]][i] = 1;
			for(int j = ed[y - 1]; j < ed[y]; ++j)
				tagy[wp[j]][i] = 1;
		}
		dfs(1);
		for(int i = 0; i < m; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
