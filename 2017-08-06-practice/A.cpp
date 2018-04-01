#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int n, m, All;
int two[50];
bool b[10][10];
int f[1 << 10], g[1 << 10], t[1 << 10], h[1 << 10];
int dp[1 << 10][1 << 10];
int ed[1 << 10], eds[1 << 10][1 << 10];

inline int getp(int S){
	return __builtin_ctz(S);
}

void init(){
	for(int S = 1; S < 1 << n; ++S){
		int p = getp(S);
		ed[S] = ed[S ^ 1 << p];
		for(int i = p + 1; i < n; ++i)
			if(S >> i & 1)
				ed[S] += !b[p][i];
	}

	for(int S = 1; S < 1 << n; ++S){
		int rS = All ^ S, p = getp(S);
		for(int T = rS; T; T = (T - 1) & rS){
			eds[S][T] = eds[S ^ 1 << p][T];
			for(int i = 0; i < n; ++i)
				if(T >> i & 1)
					eds[S][T] += !b[p][i];
		}
	}
}

void pre_work(){
	for(int S = 1; S < 1 << n; ++S){
		g[S] = 0;
		int p = getp(S);
		for(int T = (S - 1) & S; T; T = (T - 1) & S)
			if(T >> p & 1)
				g[S] = (g[S] + (ll)f[T] * two[ed[S ^ T]]) % M;
		f[S] = (two[ed[S]] + M - g[S]) % M;
	}
	
	for(int i = 0; i < All; ++i)
		dp[i][0] = 1;
	for(int S = 1; S < 1 << n; ++S){
		int rS = All ^ S, p = getp(S);
		for(int T = rS; T; T = (T - 1) & rS){
			dp[T][S] = 0;
			for(int SS = S; SS; SS = (SS - 1) & S)
				if(SS >> p & 1)
					dp[T][S] = (dp[T][S] + (ll)dp[T][S ^ SS] * f[SS] % M * eds[T][SS]) % M;
		}
	}
}

void work(){
	for(int S = 1; S < 1 << n; ++S){
		h[S] = 0;
		int p = getp(S);
		for(int T = (S - 1) & S; T; T = (T - 1) & S)
			if(T >> p & 1)
				h[S] = (h[S] + (ll)t[T] * dp[T][S ^ T]) % M;
		t[S] = (f[S] + M - h[S]) % M;
	}
}

int main(){
	two[0] = 1;
	for(int i = 1; i <= 45; ++i)
		two[i] = two[i - 1] * 2 % M;

	int Test;
	scanf("%d", &Test);
	while(Test--){
		scanf("%d%d", &n, &m);
		memset(b, 0, sizeof(b));
		for(int i = 0, u, v; i < m; ++i){
			scanf("%d%d", &u, &v);
			--u, --v;
			b[u][v] = 1;
			b[v][u] = 1;
		}

		All = (1 << n) - 1;
		init();
		pre_work();
		work();
		
		printf("%d\n", t[All]);
	}
	return 0;
}
