#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100;
int n, m;
int fa[maxn], val[maxn], sz[maxn];
bool tag[maxn];
vector<int> g[maxn];

pair<int, int> find(int x){
	int v = 0;
	while(fa[x] != x) v ^= val[x], x = fa[x];
	return mkp(x, v ^ val[x]);
}

void solve(int l, int r);

void work(int l, int r, int x, int y){
	stack<pair<int, int> > re;
	bool flag = 1;
	for(int i = x; i <= y && flag; ++i)
		for(int v : g[i])
			if(v < l || v > r){
				auto t1 = find(i), t2 = find(v);
				if(t1.fi != t2.fi){
					if(sz[t1.fi] < sz[t2.fi]) swap(t1, t2);
					fa[t2.fi] = t1.fi;
					sz[t1.fi] += sz[t2.fi];
					val[t2.fi] ^= t1.se ^ t2.se ^ 1;
					re.push(mkp(t2.fi, t1.se ^ t2.se ^ 1));
				}else if(t1 == t2) flag = 0;
			}
	if(flag) solve(l, r);
	while(!re.empty()){
		auto t = re.top(); re.pop();
		sz[fa[t.fi]] -= sz[t.fi];
		val[t.fi] ^= t.se;
		fa[t.fi] = t.fi;
	}
}

void solve(int l, int r){
	if(l == r) { tag[l] = 1; return; }
	int mid = (l + r) >> 1;
	work(l, mid, mid + 1, r);
	work(mid + 1, r, l, mid);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) g[i].clear();
		for(int i = 1; i <= m; ++i){
			static int u, v;
			scanf("%d%d", &u, &v);
			g[u].pb(v), g[v].pb(u);
		}
		for(int i = 1; i <= n; ++i) 
			fa[i] = i, sz[i] = 1, val[i] = 0, tag[i] = 0;
		solve(1, n);
		for(int i = 1; i <= n; ++i) putchar('0' + tag[i]);
		puts("");
	}
	return 0;
}
