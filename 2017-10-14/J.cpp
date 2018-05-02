#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, tim, vis[2][maxn], dep[2][maxn], que[2][maxn], L[2], R[2];
vector<int> e[maxn];
int main() {
	scanf("%d%d", &n, &m);
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	scanf("%d", &m);
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		if(u == v) {
			puts("0");
			continue;
		}
		L[0] = R[0] = L[1] = R[1] = 0;
		vis[0][u] = vis[1][v] = ++tim;
		dep[0][u] = dep[1][v] = 0;
		que[0][R[0]++] = u;
		que[1][R[1]++] = v;
		int ans = -1;
		while(ans == -1 && (L[0] < R[0] || L[1] < R[1])) {
			int dep0 = L[0] < R[0] ? dep[0][que[0][L[0]]] : n;
			int dep1 = L[1] < R[1] ? dep[1][que[1][L[1]]] : n;
			int o = dep0 > dep1;
			int u = que[o][L[o]++];
			for(auto v : e[u]) {
				if(vis[o][v] == tim)
					continue;
				vis[o][v] = tim;
				dep[o][v] = dep[o][u] + 1;
				if(vis[o ^ 1][v] == tim) {
					ans = dep[o][v] + dep[o ^ 1][v];
					break;
				}
				que[o][R[o]++] = v;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
