#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define pii pair<int, int>
#define all(a) a.begin(), a.end()

typedef long long ll;

const int inf = 1e9;
int n, m;
int b[10000];
ll p[10000];
ll ans[10000];

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i){
		ll r;
		scanf("%lld", &r);
		int o = 0;
		while(scanf("%d", &b[o]), b[o] != -1){
			scanf("%lld", &p[o]);
			o++;
		}
		
		pair<ll, int> mx = mkp(r, -inf);
		for(int i = 0; i < o; ++i)
			if(mkp(p[i], -b[i]) > mx)
				mx = mkp(p[i], -b[i]);
		if(mx.se < -m) continue;
		pair<ll, int> mx2 = mkp(r, -inf);
		for(int i = 0; i < o; ++i)
			if(-b[i] != mx.se && mkp(p[i], -b[i]) > mx2)
				mx2 = mkp(p[i], -b[i]);

		ll lim = min(mx.fi, ll(11 * mx2.fi / 10. + 0.5));
		ans[-mx.se] += lim;
	}
	int K;
	scanf("%d", &K);
	while(K--){
		int id;
		scanf("%d", &id);
		printf("%lld\n", ans[id]);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
