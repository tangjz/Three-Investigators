#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int n, m;
char s[20];
map<int, ll> mp;
map<int, int> amp;

inline ll askmax(int u){
	if(u > n) return 0;
	if(mp.count(u)) return mp[u];
	else{
		int l = u, r = u;
		while(l * 2 <= n){
			l <<= 1;
			r = (r << 1) | 1;
		}
		r = min(r, n);
		ll res = 0;
		while(r >= u) res += r, r >>= 1;
		return res;
	}
}

inline int ask(int x){
	return amp.count(x) ? amp[x] : x;
}

int main(){
	while(~scanf("%d%d", &n, &m)){
		mp.clear();
		amp.clear();
		while(m--){
			int x, v;
			scanf("%s", s);
			if(s[0] == 'c'){
				scanf("%d%d", &x, &v);
				amp[x] = v;
				for(; x; x >>= 1)
					mp[x] = max(askmax(x << 1), askmax((x << 1) | 1)) + ask(x);
			}else{
				scanf("%d", &x);
				int px = x;
				ll res = 0, now = 0;
				for(; x >> 1;){
					bool k = ~x & 1; x >>= 1;
					now += ask(x);
					ll tmp = askmax(x << 1 | k);
					if(now + tmp > res) res = now + tmp;
				}
				res += askmax(px);
				res = max(res, askmax(px << 1) + askmax(px << 1 | 1) + ask(px));
				printf("%lld\n", res);
			}
		}
	}
	return 0;
}
