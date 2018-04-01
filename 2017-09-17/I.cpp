#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 201, maxm = 1001, INF = 0x3f3f3f3f;
int t, N, M, S, T, lnk[maxn], lev[maxn], cur[maxn];
struct Edge {
	int nxt, v, w;
} e[maxm << 1 | 1];
bool bfs() {
	int L = 0, R = 0;
	static int que[maxn];
	memset(lev + 1, -1, N * sizeof(int));
	lev[S] = 0;
	que[R++] = S;
	while(L < R) {
		int u = que[L++];
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			if(lev[e[it].v] == -1 && e[it].w > 0) {
				lev[e[it].v] = lev[u] + 1;
				que[R++] = e[it].v;
			}
	}
	return lev[T] != -1;
}
int dfs(int u, int lim) {
	if(u == T)
		return lim;
	int ret = 0, tmp;
	for(int &it = cur[u]; it != -1; it = e[it].nxt)
		if(lev[e[it].v] == lev[u] + 1 && e[it].w > 0
		&& (tmp = dfs(e[it].v, min(lim - ret, e[it].w))) > 0) {
			e[it].w -= tmp;
			e[it ^ 1].w += tmp;
			if((ret += tmp) == lim)
				break;
		}
	if(!ret)
		lev[u] = -1;
	return ret;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		int n, m;
		scanf("%d%d%d%d", &n, &m, &S, &T);
		N = n;
		M = 0;
		memset(lnk + 1, -1, N * sizeof(int));
		for(int i = 0; i < m; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			w = w * (m + 1) + 1;
			e[M] = (Edge){lnk[u], v, w};
			lnk[u] = M++;
			e[M] = (Edge){lnk[v], u, 0};
			lnk[v] = M++;
		}
		int flow = 0;
		while(bfs()) {
			memcpy(cur + 1, lnk + 1, N * sizeof(int));
			for(int tmp; (tmp = dfs(S, INF)) > 0; flow += tmp);
		}
		printf("%d\n", flow % (m + 1));
	}
	return 0;
}
