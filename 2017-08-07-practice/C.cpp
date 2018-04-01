#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, n, Q, m;
vector<int> g[200100];
int w[200100], q[200100];
int f[200100];
int RMQ[2][200100][18], rmq[400100][19], re[400100], ww[200100];
bool tag[200100];
int logdown[400100];
int len[200100], po[200100];
int dep[200100];
int U, V, dia, tt, tot;

void dfs(int t, int fa){
	len[t] = 0, po[t] = t;
	for(int v : g[t]){
		if(v == fa) continue;
		dfs(v, t);
		if(len[v] + len[t] + 1 > dia){
			dia = len[v] + len[t] + 1;
			U = po[v];
			V = po[t];
		}
		if(len[v] + 1 > len[t])
			len[t] = len[v] + 1, po[t] = po[v];
	}
}

bool dfs2(int t, int fa){
	if(t == V) { tag[t] = 1; q[++tt] = t; return 1; }
	for(int v : g[t]){
		if(v == fa) continue;
		if(dfs2(v, t)) { tag[t] = 1; q[++tt] = t; return 1; }
	}
	return 0;
}

void dfs3(int t, int fa, int c){
	f[t] = c; len[c] = max(len[c], dep[t]);
	re[rmq[ww[t] = ++tot][0] = tot] = t;
	for(int v : g[t]){
		if(v == fa || tag[v]) continue;
		dep[v] = dep[t] + 1;
		dfs3(v, t, c);
		rmq[++tot][0] = ww[t];
	}
}

void build(){
	for(int k = 0; k < 2; ++k)
		for(int j = 1; j <= 17; ++j)
			for(int i = tt - (1 << j) + 1; i >= 1; --i)
				RMQ[k][i][j] = max(RMQ[k][i][j - 1], RMQ[k][i + (1 << j - 1)][j - 1]);
	for(int j = 1; j <= 18; ++j)
		for(int i = tot - (1 << j) + 1; i >= 1; --i)
			rmq[i][j] = min(rmq[i][j - 1], rmq[i + (1 << j - 1)][j - 1]);
}

int getmax(int k, int l, int r){
	int x = logdown[r - l + 1];
	return max(RMQ[k][l][x], RMQ[k][r - (1 << x) + 1][x]);
}

int getmin(int l, int r){
	int k = logdown[r - l + 1];
	return re[min(rmq[l][k], rmq[r - (1 << k) + 1][k])];
}

int lca(int u, int v){
	return getmin(min(ww[u], ww[v]), max(ww[u], ww[v]));
}

int main(){
	for(int i = 0; i <= 18; ++i)
		logdown[1 << i] = i;
	for(int i = 1; i <= 400000; ++i)
		logdown[i] = max(logdown[i], logdown[i - 1]);

	scanf("%d", &T);
	while(T--){
		tt = dia = tot = 0, U = V = 1;
		memset(tag, 0, sizeof(tag));
		scanf("%d%d%d", &n, &Q, &m);
		g[1].clear();
		for(int i = 1; i < n; ++i){
			g[i + 1].clear();
			static int u;
			scanf("%d", &u);
			g[u].pb(i + 1);
			g[i + 1].pb(u);
		}
		dfs(1, 0);
		dfs2(U, 0);
		for(int i = 1; i <= tt; ++i){
			len[q[i]] = dep[q[i]] = 0;
			w[q[i]] = i;
			dfs3(q[i], 0, q[i]);
			RMQ[0][i][0] = len[q[i]] + i;
			RMQ[1][i][0] = len[q[i]] - i;
		}
		build();

		int u, v, d, A, B, C;
		scanf("%d%d%d%d%d%d", &u, &v, &d, &A, &B, &C);
		ll sum = 0;
		for(int test = 1; test <= Q; ++test){
			static int uu, vv, ud, vd, c, maxd, ans, g, md;
			if(u == v) ans = 0;
			else if(dia < d) ans = -1;
			else{
				uu = w[f[u]], ud = dep[u];
				vv = w[f[v]], vd = dep[v];
				if(uu == vv){
					g = lca(u, v);
					if(ud + vd - 2 * dep[g] >= d) ans = 1;
					else{
						md = min(ud, vd);
						if(uu - 1 + md >= d || tt - uu + md >= d) ans = 2;
						else ans = -1;
					}
				}else{
					if(uu > vv) swap(uu, vv), swap(ud, vd);
					if(ud + vd + vv - uu >= d) ans = 1;
					else{
						if(uu - 1 + ud >= d && vv - 1 + vd >= d) ans = 2;
						else if(tt - uu + ud >= d && tt - vv + vd >= d) ans = 2;
						else{
							if(max(uu - 1 + ud, tt - uu + ud) >= d &&
								 max(vv - 1 + vd, tt - vv + vd) >= d){
								ans = 3;
								if(uu + 1 < vv){
									if(vd + 1 >= ud + vv - uu - 1) c = vv - 1;
									else if(ud >= vd + vv - uu) c = uu;
									else c = (vd + ud + vv - uu) / 2 - ud + uu;
									maxd = 0;
									if(c > uu) maxd = getmax(0, uu + 1, c) - uu + ud;
									if(c + 1 < vv) maxd = max(maxd, getmax(1, c + 1, vv - 1) + vv + vd);
									if(maxd >= d) ans = 2;
								}
							}else ans = -1;
						}
					}
				}
			}
			
			sum += test * (ans + 1);
			//printf("%d %d %d: %d\n", u, v, d, ans);
			u = (((ll)A * u + B + ans) % n) + 1;
			v = (((ll)B * v + C + ans) % n) + 1;
			d = ((ll)C * d + A + ans) % m;
		}
		printf("%lld\n", sum);
	}
	
	return 0;
}
