#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define M 1000000007
#define all(a) a.begin(), a.end()

struct line{
	int x, l, r, tag;
	line(int x = 0, int l = 0, int r = 0, int tag = 0): x(x), l(l), r(r), tag(tag) {}
	bool operator < (const line &R) const{
		return x < R.x;
	}
}l[2015];

int n;
int cnt[2015];
int a, b, c, d;

int main(){
	while(scanf("%d", &n), n){
		vector<int> q;
		for(int i = 1; i <= n; ++i){
			scanf("%d%d%d%d", &a, &b, &c, &d);
			l[2 * i - 1] = line(a, b, d, 1);
			l[2 * i] = line(c, b, d, -1);
			q.pb(b);
			q.pb(d);
		}
		sort(q.begin(), q.end());
		q.erase(unique(q.begin(), q.end()), q.end());
		for(int i = 1; i <= 2 * n; ++i){
			l[i].l = lower_bound(q.begin(), q.end(), l[i].l) - q.begin();
			l[i].r = lower_bound(q.begin(), q.end(), l[i].r) - q.begin();
		}
		int m = q.size();

		sort(l + 1, l + 2 * n + 1);
		ll ans = 0;;
		
		memset(cnt, 0, sizeof(cnt));
		for(int i = 1; i <= 2 * n; ++i){
			for(int j = 0; j < m - 1; ++j)
				ans += (ll)(cnt[j] >= 1) * (l[i].x - l[i - 1].x) * (q[j + 1] - q[j]);
			for(int j = l[i].l; j < l[i].r; ++j)
				cnt[j] += l[i].tag;
		}
		
		printf("%lld\n", ans);
	}
	printf("*\n");
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
