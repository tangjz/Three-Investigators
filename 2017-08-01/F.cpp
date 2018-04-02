#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 998244353
#define R 3
#define all(a) a.begin(), a.end()

const int N = 262144;
int n, m;
int c[N], b[N], d[N];

int inverse(int a){
	return a == 1 ? 1 : (ll)(M - M / a) * inverse(M % a) % M;
}

int POW(int a, ll b){
	int ans = 1;
	for(; b; b >>= 1, a = (ll)a * a % M)
		if(b & 1) ans = (ll)ans * a % M;
	return ans;
}

void NTT(int p[], int n, int o){
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int s = n; j ^= s >>= 1, ~j & s;);
		if(i < j) swap(p[i], p[j]);
	}
	for(int d = 0; (1 << d) < n; ++d){
		int m = 1 << d, m2 = m * 2;
		int unit_p0 = POW(R, (M - 1) / m2);
		if (o == -1) unit_p0 = inverse(unit_p0);
		for(int i = 0; i < n; i += m2){
			int unit = 1;
			for(int j = 0; j < m; ++j){
				int &p1 = p[i + j + m], &p2 = p[i + j];
				int t = (ll)unit * p1 % M;
				p1 = (p2 - t + M) % M;
				p2 = (p2 + t) % M;
				unit = (ll)unit * unit_p0 % M;
			}
		}
	}
}

int A[N], B[N], C[N];

void mul(int n, int a[], int b[]){
	int nn = n << 1;
	memset(A, 0, sizeof(int) * nn);
	memset(B, 0, sizeof(int) * nn);
	for(int i = 0; i < n; ++i) A[i] = a[i], B[i] = b[i];
	NTT(A, nn, 1), NTT(B, nn, 1);
	for(int i = 0; i < nn; ++i) C[i] = (ll)A[i] * B[i] % M;
	NTT(C, nn, -1);
	int inv = inverse(nn);
	for(int i = 0; i < nn; ++i) C[i] = (ll)C[i] * inv % M;
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 0; i <= n; ++i) scanf("%d", c + i);
		scanf("%d", &m);
		int a = 0;
		while(m--){
			static int x;
			scanf("%d", &x);
			(a += x) %= M;
		}
		a = (M - a) % M;
		for(int i = 0, fac = 1, now = 1; i <= n;){
			b[n - i] = (ll)fac * c[i] % M;
			d[i] = (ll)now * inverse(fac) % M;
			//printf("%d %d\n", b[n - i], d[i]);
			fac = (ll)fac * (++i) % M;
			now = (ll)now * a % M;
		}
		
		int nn = 0;
		while((1 << nn) <= n) ++nn;
		nn = 1 << nn;
		for(int i = n + 1; i < nn; ++i) b[i] = d[i] = 0;
		mul(nn, b, d);
		for(int i = 0, fac = 1; i <= n; fac = (ll)fac * (++i) % M){
			//printf("%d\n", C[i]);
			int x = (ll)C[n - i] * inverse(fac) % M;
			printf("%d ", x);
		}
		puts("");
	}

	return 0;
}
