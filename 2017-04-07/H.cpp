#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(), a.end()

const int maxn = 200100;
int k;
ll n;
ll a[maxn], b[maxn];
ll f[maxn];
vector<ll> q;
vector<pair<ll, ll> > p;

int main(){
	scanf("%lld%d", &n, &k);
	for(int i = 1; i <= k; ++i){
		scanf("%lld%lld", a + i, b + i);
		q.pb(a[i]);
		q.pb(b[i]);
	}
	sort(all(q));
	q.erase(unique(all(q)), q.end());
	for(int i = 1; i <= k; ++i){
		a[i] = lower_bound(all(q), a[i]) - q.begin();
		b[i] = lower_bound(all(q), b[i]) - q.begin();
		p.pb(mkp(b[i], a[i]));
		//printf("%lld %lld\n", a[i], b[i]);
	}
	sort(all(p));
	int m = q.size();
	for(int i = 1, j = 0; i <= m; ++i){
		f[i] = f[i - 1];
		while(j < k && p[j].fi == i - 1){
			f[i] = max(f[i], f[p[j].se] + q[p[j].fi] - q[p[j].se] + 1);
			++j;
		}
		//printf("%d:%lld\n", i, f[i]);
	}
	printf("%lld\n", n - f[m]);
	return 0;
}
