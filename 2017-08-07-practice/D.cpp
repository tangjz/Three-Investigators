#include <bits/stdc++.h>
using namespace std;
const int maxn = 105, maxm = 2001, INF = 0x3f3f3f3f;
int N, M, S, T, lnk[maxn], dis[maxn], sum, flow, cost;
struct Edge {
	int nxt, v, w, c;
} e[maxm << 1 | 1];
bool vis[maxn];
void addEdge(int u, int v, int w, int c) {
	e[M] = (Edge){lnk[u], v, w, c};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0, -c};
	lnk[v] = M++;
}
bool Dijkstra() {
	priority_queue<pair<int, int> > Q;
	memset(dis, 0x3f, N * sizeof(int));
	memset(vis, 0, N * sizeof(bool));
	dis[T] = 0;
	for( ; !Q.empty(); Q.pop());
	Q.push(make_pair(-dis[T], T));
	while(!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			if(!e[it ^ 1].w)
				continue;
			int v = e[it].v, tp = dis[u] + e[it ^ 1].c;
			if(tp < dis[v]) {
				dis[v] = tp;
				Q.push(make_pair(-dis[v], v));
			}
		}
	}
	if(dis[S] == INF)
		return 0;
	for(int u = 0; u < N; ++u)
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			e[it].c += dis[e[it].v] - dis[u];
	sum += dis[S];
	return 1;
}
int dfs(int u, int upp) {
	if(u == T)
		return upp;
	vis[u] = 1;
	int ret = 0, tmp;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		if(!e[it].c && !vis[e[it].v] && e[it].w
		&& (tmp = dfs(e[it].v, min(upp - ret, e[it].w))) > 0) {
			e[it].w -= tmp;
			e[it ^ 1].w += tmp;
			if((ret += tmp) == upp)
				break;
		}
	return ret;
}
void MinCostMaxFlow(int upp = INF) {
	Dijkstra();
	do while(upp > 0) {
		memset(vis, 0, N * sizeof(bool));
		int adt = dfs(S, upp);
		if(!adt)
			break;
		upp -= adt;
		flow += adt;
		cost += adt * sum;
	} while(upp > 0 && Dijkstra());
}
int main() {
	int n, upp;
	static int mat[maxn >> 1 | 1][maxn >> 1 | 1];
	while(scanf("%d", &n) == 1) {
		N = n + n + 4;
		int SS = N - 4, TT = N - 3;
		S = N - 2;
		T = N - 1;
		M = sum = flow = cost = upp = 0;
		memset(lnk, -1, N * sizeof(int));
		for(int i = 0; i < n; ++i) {
			int cnt = 0;
			for(int j = 0; j < n; ++j) {
				scanf("%d", mat[i] + j);
				cnt += mat[i][j];
			}
			upp += cnt;
			addEdge(S, i, cnt, 0);
			addEdge(SS, T, cnt, 0);
		}
		for(int i = 0; i < n; ++i) {
			int cnt = 0;
			for(int j = 0; j < n; ++j)
				cnt += mat[j][i];
			upp += cnt;
			addEdge(S, n + i, cnt, 0);
			addEdge(SS, T, cnt, 0);
		}
		for(int i = 0; i < n << 1; ++i) {
			int L, R;
			scanf("%d%d", &L, &R);
			upp += L;
			addEdge(i, T, L, 0);
			addEdge(S, TT, L, 0);
			addEdge(i, TT, R - L, 0);
		}
		for(int i = 0; i < (n * n) >> 1; ++i) {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if(mat[--x1][--y1] == mat[--x2][--y2])
				continue;
			if(mat[x1][y1] < mat[x2][y2]) {
				swap(x1, x2);
				swap(y1, y2);
			}
			if(y1 == y2) {
				addEdge(x1, x2, 1, 1);
			} else {
				addEdge(n + y1, n + y2, 1, 1);
			}
		}
		addEdge(TT, SS, INF, 0);
		MinCostMaxFlow(upp);
		if(flow < upp) {
			puts("-1");
		} else {
			printf("%d\n", cost);
		}
	}
	return 0;
}
