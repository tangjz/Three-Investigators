#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int n, m;
		scanf("%d%d", &n, &m);
		int k, t;
		scanf("%d", &k);
		int ans = 0, x, y, w;
		for(int i = 1; i <= k; ++i){
			scanf("%d%d%d", &x, &y, &w);
			if((n - x + m - y) & 1) ans ^= w;
		}
		scanf("%d", &t);
		for(int i = 1; i <= t; ++i) scanf("%d%d", &x, &y);
		scanf("%d", &t);
		for(int i = 1; i <= t; ++i) scanf("%d%d", &x, &y);
		printf("%s\n", ans ? "win" : "lose");
	}
	return 0;
}
