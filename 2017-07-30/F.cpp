#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const double eps = 1e-9;
const int maxn = 110;
int T;
int n, m;
double a[maxn][maxn], tn[maxn][maxn], b[maxn];
double ans[maxn];
int u[maxn * maxn], v[maxn * maxn], du[maxn];
bool bit[maxn][maxn];

bool gauss(){
	for(int i = 1; i <= n; ++i){
		int k = i;
		for(int j = i; j <= n; ++j)
			if(fabs(a[j][i]) > fabs(a[k][i])) k = j;
		if(fabs(a[k][i]) < eps) return 0;
		if(k != i){
			for(int j = i; j <= n + 1; ++j)
				swap(a[i][j], a[k][j]);
			for(int j = 1; j <= n; ++j)
				swap(tn[i][j], tn[k][j]);
		}
		
		for(int j = i + 1; j <= n; ++j){
			double t = a[j][i] / a[i][i];
			for(int k = i; k <= n + 1; ++k)
				a[j][k] -= a[i][k] * t;
			for(int k = 1; k <= n; ++k)
				tn[j][k] -= tn[i][k] * t;
		}
	}
	for(int i = n; i; --i){
		for(int j = i + 1; j <= n; ++j)
			if(fabs(a[i][j]) > eps){
				a[i][n + 1] -= a[i][j] * ans[j];
			}
		ans[i] = a[i][n + 1] / a[i][i];
	}
	return 1;
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		memset(du, 0, sizeof(du));
		memset(bit, 0, sizeof(bit));
		for(int i = 1; i <= m; ++i){
			scanf("%d%d", u + i, v + i);
			++u[i], ++v[i];
			du[u[i]]++;
			bit[u[i]][v[i]] = 1;
		}
		memset(a, 0, sizeof(a));
		for(int i = 1; i <= n; ++i) a[i][i] = -1;
		memset(tn, 0, sizeof(tn));
		for(int i = 1; i <= n; ++i) tn[i][i] = 1;
		for(int i = 1; i <= m; ++i)
			a[v[i]][u[i]] = 1. / du[u[i]];
		
		for(int i = 1; i <= n + 1; ++i) a[n][i] = 1;
		if(!gauss()){
			printf("INF\n");
			continue;
		}
		double res = ans[n]; int ans2 = -1;

		int i;
		for(i = 1; i < n; ++i){
			if(bit[n][i]) continue;
			memset(b, 0, sizeof(b));
			for(int j = 1; j < n; ++j)
				if(bit[n][j] || i == j) b[j] = 1. / (du[n] + 1);
			b[n] = 1;
			
			double tot = 0;
			for(int j = 1; j <= n; ++j)
				tot += tn[n][j] * b[j];
			ans[n] = a[n][n + 1] / tot;
			if(ans[n] > res + eps) res = ans[n], ans2 = i - 1;
		}
		printf("1 %d\n", ans2);
	}
	
	return 0;
}
