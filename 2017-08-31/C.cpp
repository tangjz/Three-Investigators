#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 200000;
const int B = 1000;
bitset<B> b[maxn];
int cal[maxn];
int cnt[maxn];
int n, m;
int u[maxn], v[maxn];
int to[maxn * 2 + 2], ne[maxn * 2 + 2], he[maxn], e;

inline void link(int u, int v){
	to[++e] = v, ne[e] = he[u], he[u] = e;
	++cnt[u];
}

int main(){
	while(~scanf("%d%d", &n, &m)){
		for(int i = 0; i < n; ++i) cnt[i] = 0;
		for(int i = 0; i < m; ++i){
			scanf("%d%d", u + i, v + i);
			--u[i], --v[i];
			cal[i] = 0;
		}
		for(int i = 0; i < n; i += B){
			for(int j = 0; j < n; ++j) b[j].reset(), he[j] = 0, cnt[j] = 0; e = 0;
			for(int j = 0; j < m; ++j){
				if(u[j] >= i && u[j] < i + B)
					b[v[j]].set(u[j] - i), link(v[j], u[j]);
				if(v[j] >= i && v[j] < i + B)
					b[u[j]].set(v[j] - i), link(u[j], v[j]);
			}
			for(int j = 0; j < m; ++j){
				int uu = u[j], vv = v[j];
				if(cnt[uu] > cnt[vv]) swap(uu, vv);
				for(int k = he[uu]; k; k = ne[k])
					if(b[vv][to[k] - i]) ++cal[j];
			}
		}
		ll ans = 0;
		for(int i = 0; i < m; ++i){
			ans += (ll)cal[i] * (cal[i] - 1) / 2;
		}
		printf("%lld\n", ans);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
