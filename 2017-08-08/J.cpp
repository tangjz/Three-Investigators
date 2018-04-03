#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int inf = 1000000000;
const int maxn = 40000, maxm = 4;
int n, m, K;
int a[maxn][maxm], b[maxn][maxm];
pair<ll, int> f[maxn][maxm][1 << maxm];
ll ans;

inline void ckmin(pair<ll, int> &a, pair<ll, int> b){
	(a > b) && (a = b, 1);
}

ll work(ll d){
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			for(int mask = 0; mask < 1 << m; ++mask)
				f[i][j][mask] = mkp(LONG_MAX, 0);

	f[0][0][((1 << m) - 1) ^ 1] = mkp(0, 0);
	for(int i = 0; i < n; ++i){
		for(int j = i ? 0 : 1; j < m; ++j)
			for(int mask = 0; mask < 1 << m; ++mask){
				if(j){
					if(f[i][j - 1][mask].fi == LONG_MAX) continue;
					if(~mask >> j & 1) 
						ckmin(f[i][j][mask | (1 << j)], mkp(f[i][j - 1][mask].fi + a[i - 1][j] - d, f[i][j - 1][mask].se + 1));
					if(~mask >> (j - 1) & 1) 
						ckmin(f[i][j][mask | (1 << j) | (1 << (j - 1))], mkp(f[i][j - 1][mask].fi + b[i][j - 1] - d, f[i][j - 1][mask].se + 1));
					ckmin(f[i][j][mask & ~(1 << j)], f[i][j - 1][mask]);
				}else{
					if(f[i - 1][m - 1][mask].fi == LONG_MAX) continue;
					if(~mask & 1)
						ckmin(f[i][0][mask | 1], mkp(f[i - 1][m - 1][mask].fi + a[i - 1][0] - d, f[i - 1][m - 1][mask].se + 1));
					ckmin(f[i][j][mask & ~(1 << j)], f[i - 1][m - 1][mask]);
				}
			}
	}
	
	pair<ll, int> res = f[n - 1][m - 1][0];
	for(int mask = 1; mask < 1 << m; ++mask)
		res = min(res, f[n - 1][m - 1][mask]);
	if(res.se <= K) ans = res.fi;
	return res.se;
}

int main(){
	freopen("1010.in", "r", stdin);
	freopen("1010.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d", &n, &m, &K);
		for(int i = 0; i < n - 1; ++i)
			for(int j = 0; j < m; ++j)
				scanf("%d", a[i] + j);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m - 1; ++j)
				scanf("%d", b[i] + j);
		
		ll l = 0, r = 100000000000001LL;
		while(l + 1 < r){
			ll d = (l + r) >> 1;
			if(work(d) <= K) l = d;
			else r = d;
		}
		work(l);
		printf("%lld\n", l * K + ans);
	}
	return 0;
}
