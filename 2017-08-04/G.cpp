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
	int T, ca = 0;
	scanf("%d", &T);
	while(T--){
		ll H, L;
		scanf("%lld%lld", &H, &L);
		ll d = 1, l = 0;
		ll ans = H + 1; L--;
		while(L){
			ll t = min(L, d);
			ans += t * (H - l);
			d *= 2;
			L -= t;
			l++;
		}
		printf("Case %d: %lld\n", ++ca, ans);
	}
	return 0;
}
