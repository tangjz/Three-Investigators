#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()
#define F(i, j) (i > n ? 0 : i <= 10000 ? f[i][j] : g[i - 10000][j])

int T, n;
ll f[10010][150];
ll g[10010][205];
ll s[20010];
int v[20010];

inline ll sum(int l, int r){
	return r > n ? 0 : s[r] - s[l - 1];
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i){
			scanf("%d", v + i);
			s[i] = s[i - 1] + v[i];
		}
		for(int i = n; i >= 1; --i){
			for(int j = 1; (j + 2) * (j - 1) / 2 < i; ++j){
				if(i + j - 1 > n){
					if(i <= 10000) f[i][j] = 0;
					else g[i - 10000][j] = 0;
				}else if(i + j > n){
					if(i <= 10000) f[i][j] = sum(i, i + j - 1);
					else g[i - 10000][j] = sum(i, i + j - 1);
				}else{
					if(i <= 10000)
						f[i][j] = max(sum(i, i + j - 1) - F(i + j, j), sum(i, i + j) - F(i + j + 1, j + 1));
					else 
						g[i - 10000][j] = max(sum(i, i + j - 1) - F(i + j, j), sum(i, i + j) - F(i + j + 1, j + 1));
				}
				//printf("%d %d: %lld\n", i, j, F(i, j));
			}
		}
		printf("%lld\n", f[1][1]);
	}

	
	return 0;
}
