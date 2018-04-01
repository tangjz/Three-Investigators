#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int oo = 1e9, maxn = 150, maxe = 1000;
int e = 1, to[maxe], ne[maxe], he[maxn], cap[maxe], cost[maxe];
int d[maxn], vis[maxn], ln[maxe], l, r, S, T, fl[maxn], inx, from[maxn];
ll ans;

int n, m, D;
int p[300], st[300], en[300], x[300], cnt[maxn];

void link(int x, int y, int v, int c){
	to[++e] = y, ne[e] = he[x], he[x] = e, cap[e] = 0, cost[e] = c;
	to[++e] = x, ne[e] = he[y], he[y] = e, cap[e] = v, cost[e] = -c;
}

bool spfa(){
	memset(d, 128, sizeof(d));
	d[S] = 0, fl[S] = oo;
	for(vis[ln[l = r = 1] = S] = ++inx; l <= r; vis[ln[l++]] = 0){
		for(int j = he[ln[l]]; j; j = ne[j])
			if(cap[j ^ 1] && d[to[j]] < d[ln[l]] + cost[j]){
				d[to[j]] = d[ln[l]] + cost[j];
				fl[to[j]] = min(fl[ln[l]], cap[j ^ 1]);
				from[to[j]] = j;
				if(vis[to[j]] < inx){
					vis[to[j]] = inx;
					ln[++r] = to[j];
				}
			}
	}
	if(d[T] <= 0) return 0;
	int f = fl[T]; ans += (ll)f * d[T];
	for(int t = T; t != S; t = to[from[t] ^ 1])
		cap[from[t]] += f, cap[from[t] ^ 1] -= f;
	return 1;
}

void init(){
	e = 1;
	memset(he, 0, sizeof(he));
}

ll solve(int c){
	init();
	S = 2 * n + 1, T = S + 1;
	for(int i = 1; i <= n; ++i){
		link(S, i, c, 0);
		link(i + n, T, c, 0);
	}
	ans = 0;
	for(int i = 1; i <= m; ++i)
		link(st[i], en[i] + n, p[i], x[i]);
	while(spfa());
	return ans - (ll)c * D;
}

int main(){
	int Te;
	scanf("%d", &Te);
	int ca = 0;
	while(Te--){
		scanf("%d%d%d", &n, &m, &D);
		memset(cnt, 0, sizeof(cnt));
		for(int i = 1; i <= m; ++i){
			scanf("%d%d%d%d", p + i, st + i, en + i, x + i);
			cnt[st[i]] += p[i];
			cnt[en[i] + n] += p[i];
		}
		int l = 0, r = 0;
		for(int i = 1; i <= 2 * n; ++i)
			r = max(r, cnt[i]);
		r++;
		ll res = 0;
		while(l < r - 1){
			int mid = (l + r) >> 1;
			ll v1 = solve(mid - 1), v2 = solve(mid);
			if(v1 < v2) l = mid, res = max(res, v2);
			else r = mid, res = max(res, v1);
		}
		printf("Case %d: %lld\n", ++ca, res);
	}

	return 0;
}
