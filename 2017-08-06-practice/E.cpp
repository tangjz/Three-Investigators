#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T;
int n, m, d;
vector<int> g[51];
double cnt[51];
double f[10002][51];

const int N = 51;
struct matrix{
	int n, m;
	double x[N][N];
	matrix() {}
	matrix(int n, int m) : n(n), m(m){
		memset(x, 0, sizeof(x));
	}
	matrix operator * (const matrix &R) const{
		matrix res(n, R.m);
		for(int i = 0; i < m; ++i)
			for(int j = 0; j < n; ++j)
				for(int k = 0; k < R.m; ++k)
					res.x[j][k] += x[j][i] * R.x[i][k];
		return res;
	}
	matrix operator - (const matrix &R) const{
		assert(n == R.n && m == R.m);
		matrix res(n, m);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				res.x[i][j] = x[i][j] - R.x[i][j];
		return res;
	}
	matrix operator + (const matrix &R) const{
		assert(n == R.n && m == R.m);
		matrix res(n, m);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				res.x[i][j] = x[i][j] + R.x[i][j];
		return res;
	}
	void reset(){
		assert(n == m);
		memset(x, 0, sizeof(x));
		for(int i = 0; i < n; ++i) x[i][i] = 1;
	}
};

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d", &n, &m, &d);
		for(int i = 0; i < n; ++i) g[i].clear();
		for(int i = 0, u, v; i < m; ++i){
			scanf("%d%d", &u, &v); --u, --v;
			g[u].pb(v);
			g[v].pb(u);
		}
		
		for(int p = 0; p < n; ++p){
			matrix A(n + 1, n + 1);
			for(int i = 0; i < n; ++i)
				if(i != p)
					for(int v : g[i])
						A.x[v][i] = 1. / g[i].size();
			A.x[n][p] = 1; A.x[n][n] = 1;
			matrix res(n + 1, n + 1); res.reset();
			for(int x = d + 1; x; x >>= 1, A = A * A)
				if(x & 1)
					res = res * A;
			double ans = 0;
			for(int i = 0; i < n; ++i)
				ans += res.x[n][i];
			ans /= n;
			printf("%.10f\n", 1 - ans);
		}
	}

	return 0;
}
