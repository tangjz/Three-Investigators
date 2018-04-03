#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100, N = 17;
int T, n, m;
int len[maxn], maxdp[maxn];
int size[maxn], sz[maxn];
int L[N][maxn], R[N][maxn], c[N][maxn], c2[N][maxn];
int ls[maxn * N * 2], rs[maxn * N * 2];
ll addval[maxn * N * 2];
int muldis[maxn * N * 2], adddis[maxn * N * 2];
int rt[maxn], tot;
int fa[maxn], dis[N][maxn], son[N][maxn];
vector<pair<int, int> > ed[maxn];
bool done[maxn];
int where[maxn];
int tot_size, root;
ll t1; int t2, t3;

void build(int &t, int l, int r){
	t = ++tot; addval[t] = muldis[t] = adddis[t] = 0;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(ls[t], l, mid), build(rs[t], mid + 1, r);
}

void query(int t, int l, int r, int x){
	t1 += addval[t];
	t2 += muldis[t];
	t3 += adddis[t];
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(x <= mid) query(ls[t], l, mid, x);
	else query(rs[t], mid + 1, r, x);
}

void modify(int t, int l, int r, int x, int y, int v){
	if(x <= l && y >= r){
		addval[t] -= (ll)v * t2;
		adddis[t] += v;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) modify(ls[t], l, mid, x, y, v);
	if(y > mid) modify(rs[t], mid + 1, r, x, y, v);
}

void modify2(int t, int l, int r, int x, int y, int v){
	if(x <= l && y >= r){
		addval[t] -= (ll)t3 * v;
		muldis[t] -= v;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) modify2(ls[t], l, mid, x, y, v);
	if(y > mid) modify2(rs[t], mid + 1, r, x, y, v);
}

void getroot(int t, int fa){
	size[t] = 1;
	int tmax = 0;
	for(auto e : ed[t]){
		int v = e.fi;
		if(v != fa && !done[v]){
			getroot(v, t);
			size[t] += size[v];
			tmax = max(tmax, size[v]);
		}
	}
	tmax = max(tmax, tot_size - size[t]);
	if(tmax <= tot_size / 2) root = t;
}

void dfs(int ce, int ce2, int t, int fat, int dp){
	L[dp][t] = ++sz[ce];
	if(ce != t) fa[t] = ce;
	if(t != ce && !ce2) ce2 = t;
	c[dp][t] = ce;
	c2[dp][t] = ce2;
	for(auto e : ed[t]){
		int v = e.fi, id = e.se;
		if(v != fat && !done[v]){
			son[dp][id] = v;
			maxdp[id] = dp;
			dis[dp][v] = dis[dp][t] + 1;
			dfs(ce, ce2, v, t, dp);
		}
	}
	R[dp][t] = sz[ce];
}

void work(int now, int dp){
	dis[dp][now] = 0;
	dfs(now, 0, now, 0, dp);
	build(rt[now], 1, sz[now]);
	where[now] = dp;

	getroot(root, 0);
	done[now] = 1;
	for(auto e : ed[now]){
		int v = e.fi;
		if(!done[v]){
			tot_size = size[v];
			getroot(v, 0);
			work(root, dp + 1);
		}
	}
}

int main(){
	freopen("1009.in", "r", stdin);
	freopen("1009.out", "w", stdout);
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		memset(done, 0, sizeof(done));
		memset(sz, 0, sizeof(sz));
		tot = 0;
		for(int i = 1; i <= n; ++i)
			ed[i].clear();
		for(int i = 1; i < n; ++i){
			static int u;
			scanf("%d", &u);
			len[i] = 1;
			ed[u].pb(mkp(i + 1, i));
			ed[i + 1].pb(mkp(u, i));
		}
		tot_size = n;
		getroot(1, 0);
		fa[root] = 0;
		work(root, 0);

		int Q;
		scanf("%d", &Q);
		while(Q--){
			static int ty, x, y;
			scanf("%d%d", &ty, &x);
			ty > 1 && scanf("%d", &y);
			
			if(ty == 1){
				ll res = 0;
				for(int now = x; now; now = fa[now]){
					int dp = where[now];
					t1 = t2 = t3 = 0;
					query(rt[now], 1, sz[now], L[dp][x]);
					t3 += dis[where[now]][x];
					res += t1 + (ll)t2 * t3;
				}
				printf("%lld\n", res);
			}else if(ty == 2){
				int id = x - 1;
				for(int dp = maxdp[id]; dp >= 0; --dp){
					int x = son[dp][id];
					int now = c[dp][x];
					t1 = t2 = t3 = 0;
					query(rt[now], 1, sz[now], L[dp][x]);
					modify(rt[now], 1, sz[now], L[dp][x], R[dp][x], y - len[id]);
				}
				len[id] = y;
			}else{
				for(int now = x; now; now = fa[now]){
					int dp = where[now];
					t1 = t2 = t3 = 0;
					query(rt[now], 1, sz[now], L[dp][x]);
					t3 += dis[dp][x];
					int ce2 = c2[dp][x];
					addval[rt[now]] += (ll)t3 * y;
					muldis[rt[now]] += y;
					if(ce2) modify2(rt[now], 1, sz[now], L[dp][ce2], R[dp][ce2], y);
				}
			}
		}
	}
	/*
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	*/
	return 0;
}
