#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int a, b, c, d, p, m;

ll solve(int a, int b){
	if(a < 0 || b < 0) return 0;
	a++, b++;
	ll s1 = a / p, s2 = b / p;
	ll r1 = a % p, r2 = b % p;
	ll res = s1 * s2 * p;
	res += r1 * s2;
	res += r2 * s1;

	ll mm = m;
	res += max(min(r2 - 1, mm) + min(r1 - 1, mm) - mm + 1, 0LL);
	mm += p;
	res += max(min(r2 - 1, mm) + min(r1 - 1, mm) - mm + 1, 0LL);
	return res;
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T, ca = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &p, &m);
		ll tot = (ll)(b - a + 1) * (d - c + 1);
		ll cnt = solve(b, d);
		cnt -= solve(a - 1, d);
		cnt -= solve(b, c - 1);
		cnt += solve(a - 1, c - 1);
		ll g = __gcd(cnt, tot);
		tot /= g, cnt /= g;
		printf("Case #%d: %lld/%lld\n", ++ca, cnt, tot);
	}
	

	return 0;
}
