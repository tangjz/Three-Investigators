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

const int inf = 1e9;
const int maxn = 100005;
const ll N = 1000000000000LL;
int n;
ll a[maxn], b[maxn];
int w[maxn];

int tot, rt;
int L[40 * maxn], R[40 * maxn], cnt[40 * maxn];
ll sum[40 * maxn];

void insert(int &t, ll l, ll r, ll x){
	if(!t) t = ++tot;
	if(l == r){
		sum[t] += x;
		++cnt[t];
		return;
	}
	ll mid = (l + r) >> 1;
	if(x <= mid) insert(L[t], l, mid, x);
	else insert(R[t], mid + 1, r, x);
	sum[t] = sum[L[t]] + sum[R[t]];
	cnt[t] = cnt[L[t]] + cnt[R[t]];
}

int ask(int t, ll l, ll r, ll s){
	if(l == r){
		//printf("%lld %lld %lld %d\n", l, s, sum[t], cnt[t]);
		assert(sum[t] >= s);
		return (s + l - 1) / l;
	}	
	ll mid = (l + r) >> 1;
	if(sum[R[t]] >= s) return ask(R[t], mid + 1, r, s);
	else return cnt[R[t]] + ask(L[t], l, mid, s - sum[R[t]]);
}

int main(){
	scanf("%d", &n);
	ll sum = 0;
	vector<int> q;
	for(int i = 1; i <= n; ++i){
		scanf("%lld%lld", a + i, b + i);
		sum += a[i];
		w[i] = i;
	}
	sort(w + 1, w + n + 1, [](int i, int j) { return a[i] + b[i] < a[j] + b[j]; });	
	
	ll ss = 0;
	int ans = inf;
	for(int i = 1; i <= n; ++i){
		insert(rt, 1, N, a[w[i]]);
		ss += a[w[i]];
		if(ss >= a[w[i]] + b[w[i]])
			ans = min(ans, ask(rt, 1, N, a[w[i]] + b[w[i]]));
	}
	printf("%d\n", ans == inf ? -1 : ans);
		
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
