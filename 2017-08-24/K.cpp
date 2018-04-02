#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100, maxm = maxn * 2;
const ll INF = 1LL << 60;
int n, m;
int he[maxn], to[maxm], co[maxm], ne[maxm], e, from[maxm];
ll d1[maxn], d2[maxn];
int vis[maxn];

void link(int u, int v, int w){
	to[++e] = v, co[e] = w, ne[e] = he[u], he[u] = e;
}

void dij(){
	memset(d1, 127, sizeof(ll) * (n + 1));
	memset(d2, 127, sizeof(ll) * (n + 1));
	memset(vis, 0, sizeof(int) * (n + 1));
	memset(from, 0, sizeof(int) * (n + 1));
	d1[1] = 0;
	queue<int> q; q.push(1);
	while(!q.empty()){
		int t = q.front(); q.pop();
		for(int j = he[t], v, w; j; j = ne[j]){
			v = to[j], w = co[j];
			if(d1[t] + w < d1[v]){
				from[v] = t;
				d1[v] = d1[t] + w;
				if(!vis[v]) q.push(v), vis[v] = 1;
			}
			if(d1[t] + w < d2[v] && from[v] != t){
				d2[v] = d1[t] + w;
				if(!vis[v]) q.push(v), vis[v] = 1;
			}
			if(d2[t] < INF && d2[t] + w < d2[v]){
				d2[v] = d2[t] + w;
				if(!vis[v]) q.push(v), vis[v] = 1;
			}
		}
		vis[t] = 0;
	}
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		e = 0;
		memset(he, 0, sizeof(int) * (n + 1));
		for(int i = 1; i <= m; ++i){
			static int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			link(u, v, w);
			link(v, u, w);
		}
		dij();
		printf("%lld\n", d2[n]);
	}
	return 0;
}
