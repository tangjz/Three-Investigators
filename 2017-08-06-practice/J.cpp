#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()
#define pii pair<int, int>

const double eps = 1e-10;
int n, m, S, T;
int fa[10010], faa[10010], col[10010];

const int MAXN = 500;
int to[MAXN];
bool ok[MAXN];
double ans[MAXN], a[MAXN][MAXN];

void gauss(int n){
	int lt = 1;
	for(int i = 1; i <= n; ++i){
		int k = lt;
		for(int j = lt; j <= n; ++j)
			if(fabs(a[j][i]) > fabs(a[k][i])) k = j;
		if(fabs(a[k][i]) < eps) continue;
		if(k != lt)
			for(int j = i; j <= n + 1; ++j) swap(a[lt][j], a[k][j]);
		to[lt++] = i; ok[i] = 1;
		for(int j = lt; j <= n; ++j){
			double t = a[j][i] / a[lt - 1][i];
			for(int k = i; k <= n + 1; ++k)
				a[j][k] -= a[lt - 1][k] * t;
		}
	}lt--;
	for(int i = lt; i; --i){
		for(int j = to[i] + 1; j <= n; ++j)
			if(fabs(a[i][j]) > eps){
				if(ok[j]) a[i][n + 1] -= a[i][j] * ans[j];
				else ok[to[i]] = 0;
			}
		if(ok[to[i]])
			ans[to[i]] = a[i][n + 1] / a[i][to[i]];
	}
}

int find(int fa[], int x) { return fa[x] == x ? x : fa[x] = find(fa, fa[x]); }

int main(){
	int Test;
	scanf("%d", &Test);
	while(Test--){
		scanf("%d%d%d%d", &n, &m, &S, &T);
		for(int i = 1; i <= n; ++i) fa[i] = faa[i] = i;
		vector<pii> edges;
		for(int i = 1, u, v, c; i <= m; ++i){
			scanf("%d%d%d", &u, &v, &c);
			if(c == 0){
				u = find(fa, u), v = find(fa, v);
				fa[u] = v;
			}else edges.pb(mkp(u, v));
			u = find(faa, u), v = find(faa, v);
			faa[u] = v;
		}
		if(find(fa, S) == find(fa, T)){
			puts("0.000000");
			continue;
		}
		if(find(faa, S) != find(faa, T)){
			puts("inf");
			continue;
		}
		
		int tot = 0;
		for(int i = 1; i <= n; ++i)
			if(find(fa, i) == i){
				col[i] = ++tot;
			}
		S = col[fa[S]], T = col[fa[T]];
		
		memset(a, 0, sizeof(a));
		for(pii p : edges)
			if(fa[p.fi] != fa[p.se]){
				int u = col[fa[p.fi]], v = col[fa[p.se]];
				++a[u][v], --a[u][u];
				++a[v][u], --a[v][v];				
			}
		--a[S][tot + 1];
		memset(a[T], 0, sizeof(a[T]));
		a[T][T] = 1;		
		
		gauss(tot);
		
		printf("%.6f\n", ans[S]);
	}
	return 0;
}
