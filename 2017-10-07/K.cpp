#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define all(a) a.begin(), a.end()

const double oo = (1e18) + 100;
int r, s, m, d, n, k, x;
bitset<1000> S[27], M[27], D[27];
bool ban_sm[27][27], ban_sd[27][27], ban_md[27][27];
int b[1001];

void solve(){
	ll ans = 0;
	for(int i = 1; i <= s; ++i)
		for(int j = 1; j <= m; ++j)
			if(!ban_sm[i][j])
				for(int k = 1; k <= d; ++k)
					if(!ban_sd[i][k] && !ban_md[j][k]){
						auto tmp = S[i] | M[j] | D[k];
						if(tmp.count() >= 60){
							puts("too many");
							return;
						}
						ll res = 1;
						for(int x = 0; x < r; ++x)
							if(S[i][x] || M[j][x] || D[k][x]){							
								double val = 1. * res * b[x];
								if(val > oo){
									puts("too many");
									return;
								}
								
								res = res * b[x];
							}
						
						ans = ans + res;
						if(ans > 1000000000000000000LL){
							puts("too many");
							return;
						}
					}
	printf("%lld\n", ans);
}

int main(){
	scanf("%d%d%d%d%d", &r, &s, &m, &d, &n);
	for(int i = 0; i < r; ++i)
		scanf("%d", b + i);
	
	for(int i = 1; i <= s; ++i){
		scanf("%d", &k);
		for(int j = 0; j < k; ++j){
			scanf("%d", &x); --x;
			if(b[x] == 1) continue;
			S[i].set(x);
		}
	}

	for(int i = 1; i <= m; ++i){
		scanf("%d", &k);
		for(int j = 0; j < k; ++j){
			scanf("%d", &x); --x;
			if(b[x] == 1) continue;
			M[i].set(x);
		}
	}

	for(int i = 1; i <= d; ++i){
		scanf("%d", &k);
		for(int j = 0; j < k; ++j){
			scanf("%d", &x); --x;
			if(b[x] == 1) continue;
			D[i].set(x);
		}
	}
	
	for(int i = 1, j, k; i <= n; ++i){
		scanf("%d%d", &j, &k);
		if(j > k) swap(j, k);
		if(j <= s){
			if(k <= s);
			else if(k <= s + m){
				ban_sm[j][k - s] = 1;
			}else{
				ban_sd[j][k - s - m] = 1;
			}
		}else if(j <= s + m){
			if(k <= s + m);
			else{
				ban_md[j - s][k - s - m] = 1;
			}
		}
	}
	
	solve();
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
