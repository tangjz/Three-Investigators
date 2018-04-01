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

const ll inf = 1LL << 60;

struct edge{
	int u, v, w;
	edge() {}
	edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

int tot;
struct matrix{
	int n, m;
	ll x[60][60];
	matrix() {};
	void clear(){
		memset(x, 127, sizeof(x));
	}
	matrix(int n, int m) : n(n), m(m) { clear(); }
	ll *operator [] (int a) { return x[a]; }
	void reset(){
		assert(n == m);
		clear();
		for(int i = 1; i <= tot; ++i) x[i][i] = 0;
	}
}f[10];
matrix operator * (matrix &a, matrix &b){
	assert(a.m == b.n);
	matrix p(a.n, b.m);
	for(int i = 1; i <= a.n; ++i)
		for(int j = 1; j <= a.m; ++j)
			for(int k = 1; k <= b.m; ++k)
				if(a[i][j] < inf && b[j][k] < inf)
					p[i][k] = min(p[i][k], a[i][j] + b[j][k]);
	return p;
}

int x;
inline int next(){
	return x = x * 907 % 2333333;
}

int n;

int fa[7];
int re[60][7];
ll fir[60];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int u, int v){
	fa[find(u)] = find(v);
}

map<vector<int>, int> mp;
int getsta(int n, int bg = 0){
	vector<int> v; v.resize(n);
	for(int i = 1 + bg, j, tx = 0; i <= n + bg; ++i){
		find(i);
		for(j = 1 + bg; j < i; ++j)
			if(fa[i] == fa[j]) { v[i - bg - 1] = v[j - bg - 1]; break; }
		if(j == i) v[i - bg - 1] = ++tx;
	}
	if (mp.count(v)) return mp[v];
	else{
		memcpy(re[++tot], fa, sizeof(fa));
		return mp[v] = tot;
	}
}

int init(int n){
	vector<edge> ed;
	for(int i = 2; i <= n; ++i){
		int T = next();
		for(int j = 1; j <= i - 1; ++j){
			int w = T ^ next();
			ed.pb(edge(i, j, w));
		}
	}
	
	int m = ed.size();
	memset(fir, 127, sizeof(fir));
	for(int mask = 0; mask < 1 << m; ++mask){
		for(int i = 1; i <= n; ++i) fa[i] = i;
		ll cost = 0;
		for(int i = 0; i < m; ++i)
			if(mask >> i & 1){
				merge(ed[i].u, ed[i].v);
				cost += ed[i].w;
			}
		int sta = getsta(n);
		fir[sta] = min(fir[sta], cost);
	}
	
	for(int i = 1; i <= n; ++i) fa[i] = 1;
	return getsta(n);
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		tot = 0; mp.clear();
		scanf("%d%d", &n, &x);
		
		//first 5 points
		int pre = init(min(n, 5));
		if(n <= 5) { printf("%lld\n", fir[pre]); continue; }
		
		matrix A(tot, tot);
		A.reset();

		for(int j = 0; j < 9; ++j){
			f[j] = matrix(tot, tot);
			int T = next();
			static int ed[5];
			for(int k = 0; k < 5; ++k) ed[k] = T ^ next();

			for(int preSta = 1; preSta <= tot; ++preSta){
				for(int mask = 0; mask < 1 << 5; ++mask){
					memcpy(fa, re[preSta], sizeof(re[preSta]));
					fa[6] = 6;
					ll cost = 0;
					for(int k = 0; k < 5; ++k)
						if(mask >> k & 1){
							cost += ed[k];
							merge(k + 1, 6);
						}
					bool flag = 0;
					for(int i = 2; i <= 6; ++i) flag |= find(1) == find(i);
					if(!flag) continue;
					int sta = getsta(5, 1);					
					f[j][sta][preSta] = min(f[j][sta][preSta], cost);
				}
			}
			
			A = f[j] * A;
		}
		
		matrix ans(tot, 1);
		for(int i = 1; i <= tot; ++i) ans[i][1] = fir[i];
		for(int x = (n - 5) / 9; x; x >>= 1, A = A * A)
			if(x & 1) ans = A * ans;				
			
		for(int x = 0; x < (n - 5) % 9; ++x)
			ans = f[x] * ans;
		
		printf("%lld\n", ans[pre][1]);
	}
	
	return 0;
}
