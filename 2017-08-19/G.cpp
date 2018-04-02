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
int f[40], g[40][40];
int L, R, l, r;
int a[40];

int calc(int n, int k){
	if(!n) return 0;
	int len = 0;
	while(n) a[++len] = n % k, n /= k;
	
	int res = 0;
	for(int i = 1; i < len; ++i)
		res += g[k][i];
	
	f[len] = a[len] - 1;
	
	for(int i = len - 1; i > len / 2; --i)
		f[i] = k * f[i + 1] + a[i];
	
	res += f[len / 2 + 1];
	bool flag = 1;
	for(int i = len / 2; i >= 1; --i){
		if(a[len - i + 1] > a[i]) { flag = 0; break; }
		else if(a[len - i + 1] < a[i]) break;
	}
	return res + flag;
}

int main(){
	scanf("%d", &T);

	for(int base = 2; base <= 36; ++base){
		int now = 1;
		for(int l = 1; l <= 16; ++l){
			int cnt = now * base - now;
			g[base][l * 2 - 1] = g[base][l * 2] = cnt;
			now *= base;
		}
	}
	int ca = 0;
	while(T--){
		scanf("%d%d%d%d", &L, &R, &l, &r);
		ll res = 0;
		for(int i = l; i <= r; ++i){
			int x = calc(R, i) - calc(L - 1, i);
			res += (ll)i * x + (R - L + 1 - x);
		}
		printf("Case #%d: %lld\n", ++ca, res);
	}
	return 0;
}
