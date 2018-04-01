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
#define ckmin(a, b) (a >= b ? a = b, 1 : 0)

const int maxn = 5005;
int k, n, m;
int a[maxn], b[maxn];
int fir[maxn], last[maxn];
int nex[maxn];
int f[maxn], g[maxn];
int from_f[maxn], from_g[maxn];
int dp[maxn][maxn];
pii from_dp[maxn][maxn];

void work_f(int x){
	if(from_f[x] < 0){
		printf("%d", -from_f[x]);
	}else{
		printf("%d ", a[from_f[x]]);
		work_f(from_f[x]);
	}
}

void work_g(int x){
	if(from_g[x] < 0){
		printf("%d", -from_g[x]);
	}else{
		printf("%d ", b[from_g[x]]);
		work_g(from_g[x]);
	}
}

void work_dp(int x, int y){
	if(from_dp[x][y].fi < 0){
		printf("%d", -from_dp[x][y].fi);
	}else if(from_dp[x][y].fi == 0){
		printf("%d ", b[from_dp[x][y].se]);
		work_g(from_dp[x][y].se);
	}else if(from_dp[x][y].se == 0){
		printf("%d ", a[from_dp[x][y].fi]);
		work_f(from_dp[x][y].fi);
	}else{
		printf("%d ", a[from_dp[x][y].fi]);
		work_dp(from_dp[x][y].fi, from_dp[x][y].se);
	}
}

int main(){
	freopen("robots.in", "r", stdin);
	freopen("robots.out", "w", stdout);
	scanf("%d", &k);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", a + i);
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i) scanf("%d", b + i);
	
	for(int i = n; i >= 0; --i){
		f[i] = 1e9;
		for(int j = 1; j <= k; ++j)
			if(last[j]){
				if(ckmin(f[i], f[last[j]] + 1))
					from_f[i] = last[j];
			}else f[i] = 1, from_f[i] = -j;
		last[a[i]] = i;
	}

	memset(last, 0, sizeof(last));
	for(int i = m; i >= 0; --i){
		g[i] = 1e9;
		for(int j = 1; j <= k; ++j)
			if(last[j]){
				if(ckmin(g[i], g[last[j]] + 1))
					from_g[i] = last[j];
			}else g[i] = 1, from_g[i] = -j;
		last[b[i]] = i;
	}
	
	memset(dp, 127, sizeof(dp));
	for(int i = n; i >= 0; --i){
		memset(fir, 0, sizeof(fir));
		for(int j = n; j > i; --j)
			fir[a[j]] = j;
		
		memset(last, 0, sizeof(last));
		for(int j = m; j; --j){
			nex[j] = last[b[j]];
			last[b[j]] = j;
		}
		
		for(int j = 1; j <= k; ++j)
			if(fir[j] && last[j]){
				if(ckmin(dp[i][0], dp[fir[j]][last[j]] + 1))
					from_dp[i][0] = mkp(fir[j], last[j]);
			}else if(fir[j]){
				if(ckmin(dp[i][0], f[fir[j]] + 1))
					from_dp[i][0] = mkp(fir[j], 0);
			}else if(last[j]){
				if(ckmin(dp[i][0], g[last[j]] + 1))
					from_dp[i][0] = mkp(0, last[j]);
			}else dp[i][0] = 1, from_dp[i][0] = mkp(-j, -j);
		
		for(int j = 1; j <= m; ++j){
			dp[i][j] = dp[i][j - 1];
			from_dp[i][j] = from_dp[i][j - 1];
			if(nex[j]){
				if(fir[b[j]]){
					if(ckmin(dp[i][j], dp[fir[b[j]]][nex[j]] + 1))
						from_dp[i][j] = mkp(fir[b[j]], nex[j]);
				}else
					if(ckmin(dp[i][j], g[nex[j]] + 1))
						from_dp[i][j] = mkp(0, nex[j]);
			}else{
				if(fir[b[j]]){
					if(ckmin(dp[i][j], f[fir[b[j]]] + 1))
						from_dp[i][j] = mkp(fir[b[j]], 0);
				}else
					dp[i][j] = 1, from_dp[i][j] = mkp(-b[j], -b[j]);
			}
		}
	}
	
	printf("%d\n", dp[0][0]);
	work_dp(0, 0);
	
	return 0;
}
