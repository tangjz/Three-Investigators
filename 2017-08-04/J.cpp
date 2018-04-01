#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 1010, maxk = 110;
int sz[maxn];
ll f[maxn][maxk];
int n, k;
vector<pair<int, int> > ed[maxn];
int T;

void dfs(int t){
	sz[t] = 1;
	for(auto e : ed[t]){
		int v = e.fi, w = e.se;
		dfs(v);
		for(int i = sz[t]; i >= (t == 1 ? 1 : 0); --i)
			for(int j = min(sz[v], k + 1 - i); j >= 0; --j)
				f[t][i + j] = max(f[t][i + j], f[t][i] + f[v][j] + min(j, k + 1 - j) * w * 2);
		sz[t] += sz[v];
	}
}

int main(){
	int ca = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; ++i) ed[i].clear();
		memset(f, 0, sizeof(f));
		for(int i = 2; i <= n; ++i){
			static int p, w;
			scanf("%d%d", &p, &w);
			ed[p].pb(mkp(i, w));
		}
		dfs(1);
		printf("Case %d: %lld\n", ++ca, f[1][k + 1]);
	}
	
	return 0;
}
