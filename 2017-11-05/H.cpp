#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second
#define mkp make_pair
#define pii pair<int, int>

const int maxn = 20005;
const int B = 90;
int T, n, m;
int u[2][maxn], v[2][maxn];
vector<int> g[2][maxn];
int p[2][maxn], w[2][maxn], cntp;
int q[maxn];
int fa[maxn], sz[maxn];
pii re[maxn];
int tag[maxn], inx;
int re_fa[maxn], re_sz[maxn];
int ans[maxn];
int dp[maxn], fat[maxn];

void dfs(int k, int t, int fa){
	if(!k) dp[t] = dp[fa] + 1, fat[t] = fa;
	p[k][++cntp] = t;
	w[k][t] = cntp;
	for(int v : g[k][t])
		if(v != fa)
			dfs(k, v, t);
	p[k][++cntp] = -t;
}

inline int find(int x){
	while(fa[x] != x) x = fa[x];
	return x;
}

int main(){
	freopen("h.in", "r", stdin);
	freopen("h.out", "w", stdout);
	
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int k = 0; k < 2; ++k){
			for(int i = 1; i <= n; ++i){
				scanf("%d%d", u[k] + i, v[k] + i);
				vector<int>().swap(g[k][i]);
			}
			for(int i = 1, u, v; i < n; ++i){
				scanf("%d%d", &u, &v);
				g[k][u].pb(v);
				g[k][v].pb(u);
			}
			cntp = 0;
			dfs(k, 1, 0);
		}
		
		for(int i = 1; i <= n; ++i) q[i] = i;
		sort(q + 1, q + n + 1, [](int i, int j){
				if(w[0][i] / B == w[0][j] / B) return w[1][i] < w[1][j];
				else return w[0][i] < w[0][j];
			});
		for(int i = 1, j; i <= n; i = j){
			int ii = q[i];

			for(int k = 1; k <= m; ++k) fa[k] = k, sz[k] = 1;
			int cnt = m;
			
			j = i + 1;
			int L = w[0][ii], R = w[0][ii];
			while(j <= n && w[0][q[j]] / B == w[0][ii] / B){
				L = min(L, w[0][q[j]]);
				R = max(R, w[0][q[j]]);
				j++;
			}
			int ce = abs(p[0][L]);
			for(int i = L; i <= R; ++i) 
				if(dp[abs(p[0][i])] < dp[ce]) ce = abs(p[0][i]);
			if(ce > 1) ce = fat[ce];
			for(int k = ce; k; k = fat[k]){
				int x = find(u[0][k]), y = find(v[0][k]);
				if(x == y) continue;
				if(sz[x] > sz[y]) swap(x, y);
				fa[x] = y;
				sz[y] += sz[x];
				--cnt;
			}
			
			j = i;
			int last = 0;
			while(j <= n && w[0][q[j]] / B == w[0][ii] / B){
				int jj = q[j];
				for(int k = last + 1; k <= w[1][jj]; ++k){
					if(p[1][k] > 0){
						int x = find(u[1][p[1][k]]), y = find(v[1][p[1][k]]);
						if(x == y){
							re[p[1][k]] = mkp(-1, -1);
						}else{
							if(sz[x] > sz[y]) swap(x, y);
							fa[x] = y;
							sz[y] += sz[x];
							re[p[1][k]] = mkp(x, y);
							--cnt;
						}
					}else{
						if(re[-p[1][k]].fi == -1) continue;
						int x = re[-p[1][k]].fi, y = re[-p[1][k]].se;
						fa[x] = x;
						sz[y] -= sz[x];
						++cnt;
					}
				}
				last = w[1][jj];
				
				++inx;
				vector<int> modi;
				int pre_cnt = cnt;
				for(int k = jj; k != ce; k = fat[k]){
					int x = find(u[0][k]), y = find(v[0][k]);
					if(x == y) continue;
					if(sz[x] > sz[y]) swap(x, y);
					if(tag[x] != inx) tag[x] = inx, re_fa[x] = fa[x], re_sz[x] = sz[x], modi.pb(x);
					if(tag[y] != inx) tag[y] = inx, re_fa[y] = fa[y], re_sz[y] = sz[y], modi.pb(y);
					fa[x] = y;
					sz[y] += sz[x];
					--cnt;
				}
				
				ans[jj] = cnt;

				for(int x : modi)
					fa[x] = re_fa[x], sz[x] = re_sz[x];
				cnt = pre_cnt;			
				++j;
			}
		}
		for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
		//puts("");
	}
}
