#include<bits/stdc++.h>
using namespace std;
#define y1 y114514
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define pii pair<int, int>
#define M 1000000007
#define all(a) a.begin(), a.end()
typedef long long ll;

const int maxn = 310, maxe = maxn * maxn * 3, oo = 1e9;
int e = 1, inx, vis[maxn], ln[maxn], ht[maxn], l, r, S, T;
int to[maxe], ne[maxe], he[maxn], cap[maxe];

int n, m;
int p[maxn], k[maxn], c[maxn];

void link(int x, int y, int v){
	to[++e] = y, ne[e] = he[x], he[x] = e, cap[e] = 0;
	to[++e] = x, ne[e] = he[y], he[y] = e, cap[e] = v;
}

bool bfs(){
	for(ln[l = r = 1] = S, vis[S] = ++inx, ht[S] = 1; l <= r; l++)
		for(int j = he[ln[l]]; j; j = ne[j])
			if(vis[to[j]] < inx && cap[j ^ 1]){
				vis[to[j]] = inx, ht[to[j]] = ht[ln[l]] + 1, ln[++r] = to[j];
				if(to[j] == T) return 1;
			}
	return 0;
}

int dfs(int f, int d){
	if(!f || d == S) return f;
	int flow = 0, k;
	for(int j = he[d]; j; j = ne[j])
		if(vis[to[j]] == inx && ht[to[j]] == ht[d] - 1 && (k = dfs(min(f, cap[j]), to[j]))){
			f -= k, flow += k;
			cap[j] -= k, cap[j ^ 1] += k;
			if(!f) return flow;
		}
	ht[d] = maxn + 1;
	return flow;
}

int dinic(){
	int maxflow = 0;
	while(bfs()) maxflow += dfs(oo, T);
	return maxflow;
}


void init(){
	memset(he, 0, sizeof(he));
	e = 1;
}

int main(){
	scanf("%d%d", &n, &m);
	vector<int> q;
	int sum = 0;
	for(int i = 1; i <= n; ++i){
		scanf("%d%d%d", p + i, k + i, c + i);
		q.pb(p[i]);
		q.pb(k[i]);
		sum += c[i];
	}
	sort(all(q));
	q.erase(unique(all(q)), q.end());
	int nn = q.size();
	S = n + nn, T = S + 1;
	for(int i = 1; i < nn; ++i)
		link(n + i, T, (q[i] - q[i - 1]) * m);
	for(int i = 1; i <= n; ++i){		
		int l = lower_bound(all(q), p[i]) - q.begin() + 1;
		int r = lower_bound(all(q), k[i]) - q.begin() + 1;

		link(S, i, c[i]);
		for(int j = l; j < r; ++j)
			link(i, n + j, q[j] - q[j - 1]);
	}
	sum -= dinic();
	if(sum) puts("NO");
	else puts("YES");
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
