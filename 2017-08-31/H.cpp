#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define all(a) a.begin(), a.end()

int n, a;

int POW(int a, int b, int M){
	int res = 1;
	for(; b; b >>= 1, a = (ll)a * a % M)
		if(b & 1) res = (ll)res * a % M;
	return res;
}

int main(){
	freopen("h.in", "r", stdin);
	freopen("h.out", "w", stdout);
	while(~scanf("%d%d", &n, &a)){
		if(a & 1){
			printf("1\n");
		}else{
			int res = 0;
			for(int b = 1; b <= n; ++b){
				if(POW(a, b, 1 << n) == POW(b, a, 1 << n)) ++res;
			}
			int k = 1;
			while(k * a < n) ++k;
			res += (1 << (n - k)) - (n >> k);
			printf("%d\n", res);
		}
	}
	return 0;
}
