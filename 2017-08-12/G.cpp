#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int n;
int x[110][2], y[110][2];
double d[110][110][2][2];
double f[110][110];
double g[110][110];
int from_f[110][110], from_g[110][110];

inline ll sqr(int x){
	return (ll)x * x;
}

inline bool ckmin(double &a, double b){
	return a > b ? a = b, 1 : 0;
}

void work_g(int l, int r);

void work_f(int l, int r){
	if(l > r) return;
	printf("%d+ ", r);
	if(l < r) work_f(l, from_f[l][r]), work_g(from_f[l][r] + 1, r - 1);
	printf("%d-%c", r, " \n"[r == n]);
}

void work_g(int l, int r){
	if(l > r) return;
	work_f(l, from_g[l][r]);
	work_g(from_g[l][r] + 1, r);
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 1; i <= n; ++i)
			for(int j = 0; j < 2; ++j)
				scanf("%d%d", x[i] + j, y[i] + j);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				for(int k = 0; k < 2; ++k)
					for(int l = 0; l < 2; ++l)
						d[i][j][k][l] = sqrt(sqr(x[i][k] - x[j][l]) + sqr(y[i][k] - y[j][l]));
		
		for(int len = 1; len <= n; ++len){
			for(int i = 1; i + len - 1 <= n; ++i){
				int j = i + len - 1;
				f[i][j] = g[i][j] = 1LL << 60;
				if(i == j) f[i][j] = d[i][i][0][1];
				for(int k = i; k <= j; ++k){
					if(k < j && ckmin(f[i][j], f[i][k] + d[j][k][0][0] + g[k + 1][j - 1] + d[j - 1][j][1][1]))
						from_f[i][j] = k;
					if(ckmin(g[i][j], d[i - 1][k][1][0] + f[i][k] + g[k + 1][j]))
						from_g[i][j] = k;
				}
			}
		}
		
		work_g(1, n);
	}
	
	return 0;
}
