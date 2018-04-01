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

int n, k;
double fac[205];
double f[205][25];

void init(){
	for(int i = 1; i <= n; ++i)
		fac[i] = fac[i - 1] + log(i);
}

double C(int n, int k){
	return fac[n] - fac[k] - fac[n - k];
}

int main(){
	scanf("%d%d", &n, &k);
	n -= k;
	init();
	for(int i = 1; i <= n; ++i){
		f[i][0] = i;
		if(i <= k) f[i][i] = 0;
		for(int j = 1; j <= min(i - 1, k); ++j){
			for(int t = 1; t < i; ++t){
				double cnt = 0;
				for(int p = 0; p <= min(j, t); ++p){
					if(t - p > i - j) continue;
					double tmp = C(i - j, t - p) + C(j, p) - C(i, t);
					cnt += exp(tmp) * f[i - t - (j - p)][j - p];
				}
				f[i][j] = max(f[i][j], cnt);
			}
		}
	}
	printf("%.10f\n", f[n][k]);
	
	return 0;
}
