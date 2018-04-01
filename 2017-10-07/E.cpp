#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 10005, maxe = 100005, oo = 1e9;
int e = 1, inx, vis[maxn], ln[maxn], ht[maxn], l, r, S, T;
int to[maxe], ne[maxe], he[maxn], cap[maxe];
int add[maxn], del[maxn], mul[maxn];
int a[maxn], b[maxn];
map<ll, int> mp;
int tot;
int n;

int link(int x, int y, int v){
	to[++e] = y, ne[e] = he[x], he[x] = e, cap[e] = 0;
	to[++e] = x, ne[e] = he[y], he[y] = e, cap[e] = v;
	return e - 1;
}

bool bfs(){
	for(ln[l = r = 1] = S, vis[S] = ++inx, ht[S] = 1; l <= r; ++l)
		for(int j = he[ln[l]]; j; j = ne[j])
			if(vis[to[j]] < inx && cap[j ^ 1]){
				vis[to[j]] = inx, ht[to[j]] = ht[ln[l]] + 1, ln[++r] = to[j];
				if(to[j] == T) return 1;
			}
	return 0;
}

int dfs(int f, int d){
	if(!f || d == S) return f;
	int flow = 0, k;
	for(int j = he[d]; j; j = ne[j])
		if(vis[to[j]] == inx && ht[to[j]] == ht[d] - 1 && (k = dfs(min(f, cap[j]), to[j]))){
			f -= k, flow += k;
			cap[j] -= k, cap[j ^ 1] += k;
			if(!f) return flow;
		}
	ht[d] = maxn + 1;
	return flow;
}

int dinic(){
	int maxflow = 0;
	while(bfs()) maxflow += dfs(oo, T);
	return maxflow;
}

inline int get(ll x){
	return mp.count(x) ? mp[x] : mp[x] = ++tot;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%d%d", a + i, b + i);
		int v1 = get(a[i] + b[i]);
		int v2 = get(a[i] - b[i]);
		int v3 = get((ll)a[i] * b[i]);
		
		add[i] = link(i, n + v1, 1);
		del[i] = link(i, n + v2, 1);
		mul[i] = link(i, n + v3, 1);
	}

	S = tot + n + 1, T = S + 1;
	for(int i = 1; i <= n; ++i) link(S, i, 1);
	for(int i = 1; i <= tot; ++i) link(i + n, T, 1);
	
	if(dinic() == n){
		for(int i = 1; i <= n; ++i){
			char ch; ll ans;
			if(cap[add[i]]){
				ch = '+';
				ans = a[i] + b[i];
			}else if(cap[del[i]]){
				ch = '-';
				ans = a[i] - b[i];
			}else{
				ch = '*';
				ans = (ll)a[i] * b[i];
			}
			printf("%d %c %d = %lld\n", a[i], ch, b[i], ans);
		}
	}else puts("impossible");
	
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
