#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100, Test = 16;
int T, n, m, k;
vector<pair<int, int> > g[maxn];
bool tag[maxn];
bool vis[maxn];
ll d[maxn];
int a[maxn];
ll res;

void work(){
	memset(d, 127, sizeof(d));
	memset(tag, 0, sizeof(tag));
	for(int i = 1; i <= k / 2; ++i) d[a[i]] = 0;
	for(int i = k / 2 + 1; i <= k; ++i) tag[a[i]] = 1;
	memset(vis, 0, sizeof(vis));
	priority_queue<pair<ll, int> > q;
	for(int i = 1; i <= n; ++i)
		q.push(mkp(-d[i], i));
	for(int i = 1; i <= n; ++i){
		auto t = q.top(); q.pop();		
		while(vis[t.se]) t = q.top(), q.pop();
		if(tag[t.se]) { res = min(res, d[t.se]); return; }
		vis[t.se] = 1;
		for(auto e : g[t.se]){
			int v = e.fi, w = e.se;
			if(d[t.se] + w < d[v]){
				d[v] = d[t.se] + w;
				q.push(mkp(-d[v], v));
			}
		}
	}
}

int main(){
	srand(time(0));
	int ca = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) g[i].clear();
		for(int i = 1; i <= m; ++i){			
			static int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			g[u].pb(mkp(v, w));
		}
		scanf("%d", &k);
		for(int i = 1; i <= k; ++i) scanf("%d", a + i);
		res = 1LL << 60;
		for(int t = 1; t <= Test; ++t){
			random_shuffle(a + 1, a + k + 1);
			work();
		}
		printf("Case #%d: %lld\n", ++ca, res);
	}
	return 0;
}
