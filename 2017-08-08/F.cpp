#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, n;
ll m;

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%lld", &n, &m);
		m = min((ll)n * (n - 1) / 2, m);
		if(m <= n - 1){
			ll t1 = m + 1, t2 = n - m - 1;
			ll ans = t2 * (t2 - 1) * n + t1 * t2 * n * 2;
			ans += (t1 - 1) * (t1 - 2) * 2 + (t1 - 1) * 2;
			printf("%lld\n", ans);
		}else{
			ll ans = (n - 1) * 2 + (ll)(n - 1) * (n - 2) * 2;
			m -= n - 1;
			ans -= m * 2;
			printf("%lld\n", ans);
		}
	}

	return 0;
}
