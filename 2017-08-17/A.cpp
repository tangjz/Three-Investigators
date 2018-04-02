#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100, maxp = maxn * 25;
int T;
int n, r;
int rt[maxn], q[maxn], a[maxn], cnt[maxn], po[maxp];
int ls[maxp], rs[maxp], sz[maxp];
ll tr[maxp];
ll res[maxn];
vector<int> g[maxn];

inline int newnode(){
	return po[++r] ? po[r] : r;
}

inline void del(int t){
	po[r--] = t;
}

int create(int l, int r, int x){
	int t = newnode(); tr[t] = q[x], ls[t] = rs[t] = 0, sz[t] = 1;
	if(l == r) return t;
	int mid = (l + r) >> 1;
	if(x <= mid) ls[t] = create(l, mid, x);
	else rs[t] = create(mid + 1, r, x);
	return t;
}

void insert(int& t, int l, int r, int x, ll &val){
	if(!t) t = newnode(), tr[t] = 0, ls[t] = rs[t] = 0, sz[t] = 0;
	tr[t] += q[x], ++sz[t];
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(x <= mid) val += (ll)sz[rs[t]] * q[x], insert(ls[t], l, mid, x, val);
	else val += tr[ls[t]], insert(rs[t], mid + 1, r, x, val);
}

void findall(int t, int l, int r, int tt, ll &val){
	if(!t) return;
	if(l == r){
		if(tt != -1) insert(tt, 1, n, l, val);
		del(t);
		return;
	}
	int mid = (l + r) >> 1;
	findall(ls[t], l, mid, tt, val);
	findall(rs[t], mid + 1, r, tt, val);
	del(t);
}

int merge(int t1, int t2, ll &val){
	val += tr[t2];
	findall(t2, 1, n, t1, val);
	return t1;
}

void dfs(int t, int fa){
	rt[t] = create(1, n, a[t]);
	res[t] = q[a[t]];
	for(int v : g[t]){
		if(v == fa) continue;
		dfs(v, t);
		if(sz[rt[v]] > sz[rt[t]]) res[t] = res[v], rt[t] = merge(rt[v], rt[t], res[t]);
		else rt[t] = merge(rt[t], rt[v], res[t]);
	}
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) scanf("%d", a + i), g[i].clear(), q[i] = a[i];
		sort(q + 1, q + n + 1);
		
		memset(cnt, 0, sizeof(int) * n);
		for(int i = 1; i <= n; ++i){
			a[i] = lower_bound(q + 1, q + n + 1, a[i]) - q - 1;
			++cnt[a[i]];
		}
		for(int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
		for(int i = 1; i <= n; ++i)
			a[i] = cnt[a[i]]--;

		for(int i = 1; i < n; ++i){
			static int u, v;
			scanf("%d%d", &u, &v);
			g[u].pb(v);
			g[v].pb(u);
		}
		
		dfs(1, 0);
		findall(rt[1], 1, n, -1, res[1]);
		
		for(int i = 1; i <= n; ++i) printf("%lld ", res[i]);
		printf("\n");
		//printf("%d\n", r);
	}
	
	return 0;
}
