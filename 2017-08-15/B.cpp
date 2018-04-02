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
	__int128 n, k;
	scanf("%d", &T);
	while(T--){
		ll pn, pk;
		scanf("%lld%lld", &pn, &pk); n = pn, k = pk;
		if(k == 1){
			ll res;
			if(n % 4 == 0) res = n;
			else if(n % 4 == 1) res = 1;
			else if(n % 4 == 2) res = n + 1;
			else res = 0;
			printf("%lld\n", res);
			continue;
		}
		__int128 dp = 1, l = 0, r = 0; n--;
		while(r < n){
			dp++;
			l = l * k + 1, r = (r + 1) * k;
		}
		__int128 ans = (n - l + 1) & 1; dp--;
		__int128 lt = 1, rt = 0, num = 1;
		while(dp--){
			__int128 fa = (n - 1) / k;
			__int128 fa_l = (l - 1) / k, fa_r = (r - 1) / k;
			__int128 fa_lt = lt * k + 1, fa_rt = rt * k + 1;
			__int128 l_num = fa - fa_l, r_num = fa_r - fa;
			if(l_num & 1) ans ^= fa_lt;
			if(r_num & 1) ans ^= fa_rt;
			
			__int128 fa_L = fa * k + 1, fa_R = (fa + 1) * k;
			__int128 fa_num = lt * (n - fa_L) + rt * (fa_R - n) + num + 1;
			ans ^= fa_num;

			lt = fa_lt, rt = fa_rt, l = fa_l, r = fa_r, num = fa_num;
			n = fa;
		}
		
		ll res = ans;
		printf("%lld\n", res);
	}
	return 0;
}
