#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T;
ll n;
int a[100];

int main(){
	while(~scanf("%lld", &n)){
		--n;
		int l = 0;
		ll ans = n;
		while(n) a[l++] = n & 1, n >>= 1; --l;
		ll tmp = (1LL << (l - 1)) % M * (((1LL << l) - 1) % M) % M;
		ans = (ans + tmp) % M;

		--l; while(l >= 0 && !a[l]) --l;
		if(l < 0){
			printf("%lld\n", ans);
			continue;
		}
		
		ll cnt = 0;
		for(int i = l; i >= 0; --i){
			if(a[i]){
				int tmp = (cnt + 1) % M * ((1LL << i) % M) % M;
				tmp = tmp * ((1LL << i) % M) % M;
				ans += tmp;
			}else{
				int tmp = cnt % M * ((1LL << i) % M) % M;
				tmp = tmp * ((1LL << i) % M) % M;
				ans += tmp;
			}
			ans %= M;
			cnt = cnt << 1 | a[i];
		}
		ans = (ans + n) % M;
		printf("%lld\n", ans);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
