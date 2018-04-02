#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define all(a) a.begin(), a.end()

int main(){
	int N, M;
	while(~scanf("%d%d", &N, &M)){
		ll n = 2 * N - 2, m = 2 * M - 2;
		ll g = __gcd(n, m);
		ll l1 = (n / g - 1) / 2, l2 = (m / g - 1) / 2;
		ll m1 = n / g / 2, m2 = m / g / 2;
		ll ans = n / g * m;
		ans -= l1 * (m / g) + l2 * (n / g) - l1 * l2;
		ans -= m1 * (m / g) + m2 * (n / g) - m1 * m2;
		ans -= (g - 2) / 2 * (((n / g + 1) / 2) + n / g / 2) * (((m / g + 1) / 2) + m / g / 2);
		ans -= l1 * l2;
		ans -= m1 * m2;
		printf("%lld\n", ans);
	}
	return 0;
}
