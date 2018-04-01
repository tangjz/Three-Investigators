#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

const int maxn = 100005;
const int B = 333;
struct query{
	int l, r, id;
	bool operator < (const query &R) const{
		return l / B == R.l / B ? r < R.r : l < R.l;
	}
}q[maxn];

int T, n, m, Q;
vector<int> g[maxn];
int w[maxn];
int u[maxn], v[maxn];
int L[maxn], R[maxn];
int top[maxn];
ll res[maxn];
ll ans;

int tag[maxn], inx;
int fa[maxn], re_fa[maxn], sz[maxn], re_sz[maxn];
int req[maxn], cnt;

inline int find2(int x){
	if(tag[x] != inx) tag[x] = inx, fa[x] = x, sz[x] = 1;
	return fa[x] == x ? x : fa[x] = find2(fa[x]);
}

void merge2(int x, int y){
	x = find2(x), y = find2(y);
	if(x == y) return;
	if(sz[x] > sz[y]) swap(x, y);

	ans -= (ll)sz[x] * (sz[x] - 1) / 2;
	ans -= (ll)sz[y] * (sz[y] - 1) / 2;
	
	fa[x] = y;
	sz[y] += sz[x];
	
	ans += (ll)sz[y] * (sz[y] - 1) / 2;
}

inline int find(int x){
	while(fa[x] != x) x = fa[x];
	return x;
}

void merge(int x, int y){
	x = find(x), y = find(y);
	if(x == y) return;
	if(sz[x] > sz[y]) swap(x, y);

	ans -= (ll)sz[x] * (sz[x] - 1) / 2;
	ans -= (ll)sz[y] * (sz[y] - 1) / 2;

	if(tag[x] < inx) tag[x] = inx, re_fa[x] = fa[x], re_sz[x] = sz[x], req[++cnt] = x;
	if(tag[y] < inx) tag[y] = inx, re_fa[y] = fa[y], re_sz[y] = sz[y], req[++cnt] = y;
	
	fa[x] = y;
	sz[y] += sz[x];
	
	ans += (ll)sz[y] * (sz[y] - 1) / 2;
}

inline int find1(int x){
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge1(int x, int y){
	x = find1(x), y = find1(y);
	if(x == y) return;
	if(sz[x] > sz[y]) swap(x, y);

	ans -= (ll)sz[x] * (sz[x] - 1) / 2;
	ans -= (ll)sz[y] * (sz[y] - 1) / 2;

	fa[x] = y;
	sz[y] += sz[x];
	
	ans += (ll)sz[y] * (sz[y] - 1) / 2;
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d", &n, &m, &Q);
		for(int i = 1; i <= n; ++i) vector<int>().swap(g[i]);
		for(int i = 1; i <= m; ++i){
			scanf("%d%d", u + i, v + i);
			g[u[i]].pb(i);
			g[v[i]].pb(i);
		}
		
		int tot = 0;
		for(int i = 1; i <= n; ++i){
			L[i] = tot + 1;
			for(int v : g[i]){
				w[++tot] = v;
				top[tot] = i;
			}
			R[i] = tot;
		}
		
		for(int i = 1; i <= Q; ++i){
			scanf("%d%d", &q[i].l, &q[i].r);
			q[i].id = i;
	
			int pl = q[i].l, pr = q[i].r;
		
			q[i].l = L[q[i].l];
			q[i].r = R[q[i].r];
			
			if(q[i].l / B >= q[i].r / B){
				++inx;
				ans = 0;
				
				for(int p = q[i].l; p <= q[i].r; ++p)
					if(u[w[p]] >= pl && u[w[p]] <= pr && v[w[p]] >= pl && v[w[p]] <= pr)
						merge2(u[w[p]], v[w[p]]);
				
				res[i] = ans;
			}
		}
		
		sort(q + 1, q + Q + 1);
		
		for(int i = 1, j = 1; i <= Q; i = j){

			int lim = L[top[min((q[i].l / B + 1) * B - 1, 2 * m)]] - 1;
			int last = lim;

			ans = 0;
			for(int p = 1; p <= n; ++p) fa[p] = p, sz[p] = 1;

			while(j <= Q && q[i].l / B == q[j].l / B){
				if(q[j].l / B >= q[j].r / B) { j = j + 1; continue; }
				++inx;
				cnt = 0;

				for(int p = last + 1; p <= q[j].r; ++p){
					int x = u[w[p]], y = v[w[p]];
					if(x >= top[lim + 1] && y >= top[lim + 1] && x <= top[p] && y <= top[p])
						merge1(x, y);
				}
				last = q[j].r;
				ll reans = ans;
				
				for(int p = lim; p >= q[j].l; --p){
					int x = u[w[p]], y = v[w[p]];
					if(x >= top[p] && y >= top[p] && x <= top[last] && y <= top[last])
						merge(x, y);
				}
				
				for(int p = 1; p <= cnt; ++p){
					int x = req[p];
					fa[x] = re_fa[x];
					sz[x] = re_sz[x];
				}
				
				res[q[j].id] = ans;
				
				ans = reans;
				
				j = j + 1;
			}
		}
		
		for(int i = 1; i <= Q; ++i)
			printf("%lld\n", res[i]);
	}
	return 0;
}
