#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 20009;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
char buf[maxn];
map<string, int> Hash;
int t, n, m, tot, lnk[maxn], pre[maxn], aux[maxn];
LL dis[maxn];
bool inq[maxn];
struct Edge {
	int nxt, v, w, c;
} e[maxn << 3 | 1];
void addEdge(int u, int v, int f, int c) {
	e[tot] = (Edge){lnk[u], v, f, c};
	lnk[u] = tot++;
	e[tot] = (Edge){lnk[v], u, 0, -c};
	lnk[v] = tot++;
}
bool BellmanFord(int S, int T, int &flow, LL &cost) {
	memset(dis, 0x3f, n * sizeof(LL));
	memset(inq, 0, n * sizeof(bool));
	dis[S] = 0, inq[S] = 1, pre[S] = 0, aux[S] = ~0u >> 1;
	queue<int> Q;
	Q.push(S);
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		inq[u] = 0;
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			if(e[it].w > 0 && dis[e[it].v] > dis[u] + e[it].c) {
				dis[e[it].v] = dis[u] + e[it].c;
				pre[e[it].v] = it;
				aux[e[it].v] = min(aux[u], e[it].w);
				if(!inq[e[it].v]) {
					Q.push(e[it].v);
					inq[e[it].v] = 1;
				}
			}
	}
	if(dis[T] == INF)
		return 0;
	flow += aux[T];
	cost += aux[T] * dis[T];
	for(int u = T; u != S; u = e[pre[u] ^ 1].v) {
		e[pre[u]].w -= aux[T];
		e[pre[u] ^ 1].w += aux[T];
	}
	return 1;
}
int getID(string buf) {
	if(Hash.count(buf))
		return Hash[buf];
	n += 2;
	lnk[n - 2] = lnk[n - 1] = -1;
	addEdge(n - 2, n - 1, 1, 0);
	return Hash[buf] = n - 2;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		n = tot = 0;
		map<string, int>().swap(Hash);
		getID((string)"Shanghai"); // 0 -> 1
		getID((string)"Dalian"); // 2 -> 3
		getID((string)"Xian"); // 4 -> 5
		scanf("%d", &m);
		while(m--) {
			int u, v, w;
			scanf("%s", buf);
			u = getID(buf);
			scanf("%s%d", buf, &w);
			v = getID(buf);
			addEdge(u + 1, v, 1, w);
			addEdge(v + 1, u, 1, w);
		}
		n += 2;
		int S = n - 2, T = n - 1;
		lnk[S] = lnk[T] = -1;
		addEdge(S, 1, 2, 0); // S -> 1
		addEdge(3, T, 1, 0); // 3 -> T
		addEdge(5, T, 1, 0); // 5 -> T
		int flow = 0;
		LL cost = 0;
		while(BellmanFord(S, T, flow, cost));
		if(flow < 2)
			puts("-1");
		else
			printf("%lld\n", cost);
	}
	return 0;
}
