#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 50005, maxk = 35;
int n, k;
ll pri[maxk];
ll p[maxn];
int w[maxn][maxk];

int root, tot_size;
int size[maxn];
bool done[maxn];
vector<int> g[maxn];
ll ans;
map<ll, int> mp;

void getroot(int t, int fa){
	size[t] = 1;
	int tmax = 0;
	for(auto v : g[t]){
		if(v == fa || done[v]) continue;
		getroot(v, t);
		size[t] += size[v];
		tmax = max(tmax, size[v]);
	}
	tmax = max(tmax, tot_size - size[t]);
	if(tmax <= tot_size / 2) root = t;
}

int wnow[maxk];
void dfs(int t, int fa){
	ll has = 0;
	for(int i = 0; i < k; ++i){
		wnow[i] = (wnow[i] + w[t][i]) % 3;
		int x = wnow[i] == 0 ? 0 : 3 - wnow[i];
		has = has * 3 + x;
	}
	ans += mp[has];
	for(auto v : g[t]){
		if(v == fa || done[v]) continue;
		dfs(v, t);
	}
	for(int i = 0; i < k; ++i) wnow[i] = (wnow[i] - w[t][i] + 3) % 3;
}

void dfs2(int t, int fa){
	ll has = 0;
	for(int i = 0; i < k; ++i){
		wnow[i] = (wnow[i] + w[t][i]) % 3;
		has = has * 3 + wnow[i];
	}
	++mp[has];
	for(auto v : g[t]){
		if(v == fa || done[v]) continue;
		dfs2(v, t);		
	}
	for(int i = 0; i < k; ++i) wnow[i] = (wnow[i] - w[t][i] + 3) % 3;
}

void work(int now){
	mp.clear();
	ll has = 0;
	for(int i = 0; i < k; ++i)
		has = has * 3 + w[now][i];
	if(has == 0) ans++;
	++mp[has];

	for(auto v : g[now]){
		if(done[v]) continue;
		memset(wnow, 0, sizeof(wnow));
		dfs(v, now);
		memcpy(wnow, w[now], sizeof(wnow));
		dfs2(v, now);
	}	

	getroot(root, 0);
	done[now] = 1;
	for(auto v : g[now]){
		if(done[v]) continue;
		tot_size = size[v];
		getroot(v, 0);
		work(root);
	}
}

int main(){
	while(~scanf("%d", &n)){
		scanf("%d", &k);
		for(int i = 0; i < k; ++i) scanf("%lld", pri + i);
		for(int i = 1; i <= n; ++i){
			scanf("%lld", p + i);
			for(int j = 0; j < k; ++j){
				int cnt = 0;
				while(p[i] % pri[j] == 0) p[i] /= pri[j], ++cnt;
				w[i][j] = cnt % 3;
			}
			g[i].clear();
			done[i] = 0;
		}
		for(int i = 1; i < n; ++i){
			static int u, v;
			scanf("%d%d", &u, &v);
			g[u].pb(v), g[v].pb(u);
		}
		tot_size = n;
		getroot(1, 0);
		ans = 0;
		work(root);
		printf("%lld\n", ans);
	}

	return 0;
}
