#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 50100;
struct Dis{
	int len, tmp;
	Dis() { len = tmp = 0; }
	Dis(int len, int tmp) : len(len), tmp(tmp) {}
	Dis operator + (const Dis &R) const{
		return Dis(len + R.len, min(tmp, R.tmp));
	}
	bool operator < (const Dis &R) const{
		return mkp(len, tmp) < mkp(R.len, R.tmp);
	}
}rt[maxn], db[maxn], f[maxn][18];
int n, q, T;
int b[maxn];
bool has[maxn];
int dep[maxn];
int fa[maxn][18];

Dis lca(int u, int v){
	if(dep[u] > dep[v]) swap(u, v);
	int len = dep[v] - dep[u];
	Dis res;
	for(int i = 0; i <= 16; ++i)
		if(len >> i & 1) res = res + f[v][i], v = fa[v][i];
	if(u == v) return res + db[u];
	for(int i = 16; i >= 0; --i)
		if(fa[u][i] != fa[v][i]){
			res = res + f[u][i] + f[v][i];
			u = fa[u][i], v = fa[v][i];
		}
	return res + f[u][0] + f[v][0] + db[fa[u][0]];
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &q);
		memset(has, 0, sizeof(bool) * (n + 1));
		for(int i = 2; i <= n; ++i){
			memset(fa[i], 0, sizeof(fa[i]));
			scanf("%d", fa[i] + 0);
			dep[i] = dep[fa[i][0]] + 1;
			has[fa[i][0]] = 1;
		}
		for(int i = 1; i <= n; ++i)
			scanf("%d", b + i), db[i] = Dis(b[i], -b[i]);

		//rt[1] = db[1];
		for(int i = 2; i <= n; ++i){
			f[i][0] = db[i];
			for(int j = 1; fa[i][j - 1]; ++j){
				fa[i][j] = fa[fa[i][j - 1]][j - 1];
				f[i][j] = f[i][j - 1] + f[fa[i][j - 1]][j - 1];
			}
			rt[i] = rt[fa[i][0]] + db[i];
		}
		for(int i = n; i >= 2; --i){
			if(!has[i]) rt[i] = min(rt[i], db[i]);
			rt[fa[i][0]] = min(rt[fa[i][0]], rt[i] + db[fa[i][0]]);			
		}
		for(int i = 2; i <= n; ++i)
			rt[i] = min(rt[i], rt[fa[i][0]] + db[i]);
		while(q--){
			static int u, v;
			scanf("%d%d", &u, &v);
			Dis res = min(lca(u, v), rt[u] + rt[v] + db[1]);
			if(u == v) res = db[u];
			printf("%d %d\n", res.len, -res.tmp);
		}
	}
	return 0;
}
