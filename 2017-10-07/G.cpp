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

const int maxn = 200005;
int a[maxn], b[maxn], c[maxn], w[maxn], wb[maxn], wc[maxn], p[maxn];
int cc[maxn], tag[maxn], inx;
int n;
ll ans;

void add(int x){
	for(; x <= n; x += x & -x)
		if(tag[x] == inx) ++cc[x];
		else tag[x] = inx, cc[x] = 1;
}

int ask(int x){
	int res = 0;
	for(; x; x -= x & -x)
		if(tag[x] == inx) res += cc[x];
	return res;
}

void solve(int l, int r){
	if(l == r) return;
	int mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1, r);
	
	for(int i = l; i <= r; ++i) p[i] = i;
	sort(p + l, p + r + 1, [](int i, int j) { return wb[i] < wb[j]; });
	++inx;
	for(int i = l; i <= r; ++i){
		int x = p[i];
		if(x <= mid) add(wc[x]);
		else ans += ask(wc[x]);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", a + i), w[a[i]] = i;
	for(int i = 1; i <= n; ++i) scanf("%d", b + i), b[i] = w[b[i]], wb[b[i]] = i;
	for(int i = 1; i <= n; ++i) scanf("%d", c + i), c[i] = w[c[i]], wc[c[i]] = i;
	
	solve(1, n);

	printf("%lld\n", ans);
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
