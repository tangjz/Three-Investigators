#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 1001000;
int n, k;
vector<pair<int, int> > g[maxn];
int sz[maxn];
ll ans;

void dfs(int t, int fa){
	sz[t] = 1;
	for(auto e : g[t]){
		int v = e.fi, w = e.se;
		if(v == fa) continue;
		dfs(v, t);
		sz[t] += sz[v];
		ans += (ll)min(sz[v], k) * w;
	}
}

int main(){
	while(~scanf("%d%d", &n, &k)){
		for(int i = 1; i <= n; ++i) g[i].clear();
		for(int i = 1; i < n; ++i){
			static int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			g[u].pb(mkp(v, w));
			g[v].pb(mkp(u, w));
		}
		ans = 0;
		dfs(1, 0);
		printf("%lld\n", ans);
	}
	
	return 0;
}
