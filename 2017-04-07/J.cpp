#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(), a.end()

const int maxn = 200100;
int n, q;
ll a[maxn];
ll tr[maxn * 4];
ll ret = 0;

void build(int t, int l, int r){
	if(l == r){
		tr[t] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(t << 1, l, mid);
	build((t << 1) | 1, mid + 1, r);
	tr[t] = min(tr[t << 1], tr[(t << 1) | 1]);
}

int ask(int t, int l, int r, int x, int y, ll val){
	if(x > r || y < l) return 0;
	int mid = (l + r) >> 1;
	if(l >= x && r <= y){
		if(tr[t] > val) return 0;
		if(l == r) return ret = a[l], l;
		if(tr[t << 1] <= val) return ask(t << 1, l, mid, x, y, val);
		else return ask((t << 1) | 1, mid + 1, r, x, y, val);
	}
	int k;
	if(!(k = ask(t << 1, l, mid, x, y, val)))
		return ask((t << 1) | 1, mid + 1, r, x, y, val);
	else return k;
}

int main(){
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i) scanf("%lld", a + i);
	build(1, 1, n);
	while(q--){
		int t, l, r; ll v;
		scanf("%lld%d%d", &v, &l, &r);
		while((t = ask(1, 1, n, l, r, v)) && l <= r){
			v = v % ret;
			l = t + 1;
		}
		printf("%lld\n", v);
	}
	return 0;
}
