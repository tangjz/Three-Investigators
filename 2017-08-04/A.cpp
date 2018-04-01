#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int x, n, y, m;

int main(){
	int T, ca = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d%d", &x, &n, &y, &m);
		ll p = x, q = 0;
		for(int i = 1; i <= n; ++i){
			q += p;
			swap(p, q);
		}
		p += y;
		//printf("%lld %lld\n", p, q);
		printf("Case %d: %lld\n", ++ca, __gcd(p, q));
	}
	return 0;
}
