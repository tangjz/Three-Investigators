#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 300010;
int n, m, k;
bool nop[maxn];
int pri[maxn], mu[maxn], tot;
int fac[maxn], inv[maxn];
int a[maxn];
int cnt[maxn], cal[maxn];
int f[maxn], g[maxn];

void init(){
	mu[1] = 1;
	for(int i = 2; i < maxn; ++i){
		if(!nop[i]) pri[++tot] = i, mu[i] = -1;
		for(int j = 1; j <= tot && i * pri[j] < maxn; ++j){
			nop[i * pri[j]] = 1;
			if(i % pri[j]) mu[i * pri[j]] = -mu[i]; else{
				mu[i * pri[j]] = 0;
				break;
			}
		}
	}
}

int pow(int a, int b){
	int res = 1;
	for(; b; b >>= 1, a = (ll)a * a % M)
		if(b & 1) res = (ll)res * a % M;
	return res;
}

int C(int n, int m){
	return (ll)fac[n] * inv[m] % M * inv[n - m] % M;
}

int main(){
	fac[0] = inv[0] = 1;
	for(int i = 1; i < maxn; ++i) fac[i] = (ll)fac[i - 1] * i % M, inv[i] = pow(fac[i], M - 2);
	init();
	while(~scanf("%d%d%d", &n, &m, &k)){
		for(int i = 1; i <= m; ++i) cnt[i] = cal[i] = 0;
		for(int i = 1; i <= n; ++i) scanf("%d", a + i), cnt[a[i]]++;
		for(int i = 1; i <= m; ++i)
			for(int j = i; j <= m; j += i)
				cal[i] += cnt[j];
		for(int i = 1; i <= m; ++i){
			int x = cal[i], y = n - cal[i];
			if(y > k) f[i] = 0;
			else f[i] = (ll)pow(m / i, y) * C(x, k - y) % M * pow(m / i - 1, k - y) % M;
			g[i] = 0;
		}
		for(int i = 1; i <= m; ++i)
			for(int j = i; j <= m; j += i)
				g[i] = (((g[i] + f[j] * mu[j / i]) % M) + M) % M;
		for(int i = 1; i <= m; ++i)
			printf("%d%c", g[i], " \n"[i == m]);
	}
	
	return 0;
}
