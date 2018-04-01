#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define FOR(i, l, r) for(int i = l; i <= r; i++)
#define ROF(i, r, l) for(int i = r; i >= l; i--)
#define all(a) a.begin(), a.end()
inline int ckmax(int &a, int b) { return a < b ? a = b, 1 : 0; }
inline int ckmin(int &a, int b) { return a > b ? a = b, 1 : 0; }
#define clean(a) memset(a, 0, sizeof(a))

ll A, B;
int a[25], b[25], n, m;

int main(){
	cin >> B >> A;
	ll ans = A;
	while(A) a[++n] = A % 10, A /= 10;
	while(B) b[++m] = B % 10, B /= 10;
	
	ll tans = 0, now = 1, num = 0;
	bool flag = 0;
	for(int l = n; l; --l){
		if(a[l] != b[l]) flag = 1;
		if(flag && a[l]){
			ll res = now * (a[l] - 1), res_num = num * 10 + a[l] - 1;
			if(res_num == 0) res = 1;
			for(int i = 1; i < l; ++i) res *= 9, res_num = res_num * 10 + 9;
			if(res > tans) tans = res, ans = res_num;
		}
		num = num * 10 + a[l];
		now = now * a[l];
	}
	if(now > tans) tans = now, ans = num;
	cout << ans << '\n';
  return 0;
}

