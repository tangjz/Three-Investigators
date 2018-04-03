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

const int maxn = 300005;
int n;
int x[maxn], y[maxn], w[maxn];
int top;
pii q[maxn], qq[maxn];
ll ans;

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%d%d", x + i, y + i);
		w[i] = i;
	}
	++n; w[n] = n;
	x[n] = 1 << 30;

	sort(w + 1, w + n + 1, [](int i, int j) { return x[i] < x[j] || (x[i] == x[j] && y[i] < y[j]); });
	for(int i = 1, j = 0; i <= n; i = j + 1){
		int ttop = top; top = 0;
		for(int k = 1; k <= ttop; ++k){
			auto v = q[k];
			int len = (v.se - v.fi + 2) >> 1;
			if(len <= x[w[i]] - x[w[j]])
				ans += (ll)len * (len + 1) / 2;
			else{
				int h = x[w[i]] - x[w[j]];
				ans += (ll)(len + (len - (h - 1))) * h / 2;
				q[++top] = mkp(v.fi + h, v.se - h);
			}
		}
		
		if(i == n) break;
		
		j = i; while(x[w[j + 1]] == x[w[i]]) ++j;
		
		ttop = top;
		for(int k = 1; k <= top; ++k) qq[k] = q[k];
		top = 0;

		int l = 1;
		for(int k = i; k <= j; ++k){
			while(l <= ttop && qq[l].fi <= y[w[k]]) q[++top] = qq[l++];
			if(l > 1 && qq[l - 1].se >= y[w[k]]) continue;
			q[++top] = mkp(y[w[k]], y[w[k]]);
		}
		for(int k = l; k <= ttop; ++k) q[++top] = qq[k];
		
		if(!top) continue;
		ttop = top; top = 1;		
		for(int k = 2; k <= ttop; ++k){
			if(q[k].fi == q[top].se + 2)
				q[top].se = q[k].se;
			else
				q[++top] = q[k];
		}
		/*
		for(int k = 1; k <= top; ++k)
			printf("%d %d\n", q[k].fi, q[k].se);
		puts("");
		*/
	}
	
	printf("%lld\n", ans);
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
