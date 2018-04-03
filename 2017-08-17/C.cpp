#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100010;
const double inf = 1e20;
struct node{
	int d, v, w;
	bool operator < (const node &a) const{
		return w > a.w;
	}
}a[maxn];
pair<double, int> c[maxn], d[maxn], e[maxn], f[maxn];
int q[maxn];
int n, L, maxw, pre[maxn];
int T;

pair<double, int> ask1(int x){
	pair<double, int> res = mkp(-inf, 0);
	for(; x; x -= x & -x) res = max(res, c[x]);
	return res;
}

void add1(int x, pair<double, int> v){
	for(; x <= n; x += x & -x) c[x] = max(v, c[x]);
}

pair<double, int> ask2(int x){
	pair<double, int> res = mkp(inf, 0);
	for(; x; x -= x & -x) res = min(res, d[x]);
	return res;
}

void add2(int x, pair<double, int> v){
	for(; x <= n; x += x & -x) d[x] = min(v, d[x]);
}

pair<double, int> ask3(int x){
	pair<double, int> res = mkp(inf, 0);
	for(; x <= n; x += x & -x) res = min(res, e[x]);
	return res;
}

void add3(int x, pair<double, int> v){
	for(; x; x -= x & -x) e[x] = min(v, e[x]);
}

pair<double, int> ask4(int x){
	pair<double, int> res = mkp(-inf, 0);
	for(; x <= n; x += x & -x) res = max(res, f[x]);
	return res;
}

void add4(int x, pair<double, int> v){
	for(; x; x -= x & -x) f[x] = max(v, f[x]);
}

bool check(double t){
	for(int i = 1; i <= n; ++i)
		c[i] = f[i] = mkp(-inf, 0), d[i] = e[i] = mkp(inf, 0);
	for(int i = 0, j; i < n; i = j){
		if(a[i].w != maxw)
			for(j = i; j < n && a[j].w == a[i].w; ++j){
				double s1 = q[a[j].d] + a[j].v * t;
				double s2 = s1 - L;
				
				auto tmp = ask1(a[j].d + 1);
				if(tmp.fi >= s1) pre[j] = tmp.se;
				else{
					tmp = ask2(a[j].d + 1);
					if(tmp.fi <= s2) pre[j] = tmp.se;
					else{
						tmp = ask3(a[j].d + 1);
						if(s1 >= tmp.fi) pre[j] = tmp.se;
						else{
							tmp = ask4(a[j].d + 1);
							if(s1 <= tmp.fi) pre[j] = tmp.se;
							else return 0;
						}
					}
				}
			}
		for(j = i; j < n && a[j].w == a[i].w; ++j){
			double s1 = q[a[j].d] + a[j].v * t;
			double s2 = s1 - L;
			
			add1(a[j].d + 1, mkp(s1, j));
			add2(a[j].d + 1, mkp(s1, j));
			add3(a[j].d + 1, mkp(s1, j));
			add4(a[j].d + 1, mkp(s2, j));
		}
	}
	return 1;
}

pair<int, int> getTime(int i, int j){
	if(a[i].v < a[j].v) swap(i, j);
	if(a[i].d < a[j].d) return mkp(q[a[j].d] - q[a[i].d], a[i].v - a[j].v);
	else return mkp(L - q[a[i].d] + q[a[j].d], a[i].v - a[j].v);
}

int main(){
	freopen("1003.in", "r", stdin);
	freopen("1003.out", "w", stdout);
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n ,&L);
		for(int i = 0; i < n; ++i)
			scanf("%d", &a[i].d), q[i] = a[i].d;
		sort(q, q + n);
		for(int i = 0; i < n; ++i)
			a[i].d = lower_bound(q, q + n, a[i].d) - q;
		for(int i = 0; i < n; ++i)
			scanf("%d", &a[i].v);
		maxw = 0;
		for(int i = 0; i < n; ++i){
			scanf("%d", &a[i].w);
			maxw = max(a[i].w, maxw);
		}
		sort(a, a + n);
		
		double l = 0, r = 1e9;
		for(int i = 1; i <= 100; ++i){
			double d = (l + r) / 2;
			if(check(d)) r = d;
			else l = d;
		}
		
		int up = 0, down = 1;
		for(int i = 0; i < n; ++i)
			if(a[i].w != maxw){
				auto tmp = getTime(pre[i], i);
				if((ll)up * tmp.se < (ll)down * tmp.fi)
					up = tmp.fi, down = tmp.se;
			}
		int g = __gcd(up, down);
		up /= g, down /= g;
		//printf("%.10f ", r);
		if(up)
			printf("%d/%d\n", up, down);
		else
			printf("0\n");
	}
	return 0;
}
