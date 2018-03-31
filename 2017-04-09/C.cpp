#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 41, maxp = 1143, maxm = 8, maxs = 1 << 8 | 1, INF = 0x3f3f3f3f;
const int maxd = 6, dx[maxd] = {-1, -1, 0, 0, 1, 1}, dy[maxd] = {-1, 0, -1, 1, 0, 1};
int t, n, m, tot, x[maxp], y[maxp], pos[maxn][maxn], s[maxp], w[maxp], f[maxs][maxp];
std::priority_queue<std::pair<int, int> > Q;
bool vis[maxp];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		tot = 0;
		memset(f, 0x3f, sizeof f);
		memset(pos, -1, sizeof pos);
		for(int px = 1, ctr = 0; px < n << 1; ++px) {
			int L = px < n ? 1 : px - n + 1;
			int R = px < n ? n + px : n << 1;
			for(int py = L; py < R; ++py) {
				char op[2];
				scanf("%s", op);
				if(op[0] == '*') {
					s[tot] = 1 << (ctr++);
					w[tot] = 0;
					f[s[tot]][tot] = 0;
				} else {
					s[tot] = 0;
					w[tot] = 1;
				}
				x[tot] = px;
				y[tot] = py;
				pos[px][py] = tot++;
			}
		}
		for(int msk = 0; msk < 1 << m; ++msk) {
			int *dis = f[msk];
			for(int i = 0; i < tot; ++i) {
				if(s[i] && !(msk & s[i]))
					continue;
				for(int msk2 = msk; msk2; msk2 = (msk2 - 1) & msk) {
					int tmp = f[msk2 | s[i]][i] + f[(msk ^ msk2) | s[i]][i] - w[i];
					if(tmp < dis[i])
						dis[i] = tmp;
				}
				if(dis[i] < INF)
					Q.push(std::make_pair(-dis[i], i));
			}
			memset(vis, 0, sizeof vis);
			while(!Q.empty()) {
				int u = Q.top().second;
				Q.pop();
				if(vis[u])
					continue;
				vis[u] = 1;
				int ux = x[u], uy = y[u];
				for(int o = 0; o < maxd; ++o) {
					int vx = ux + dx[o], vy = uy + dy[o], v = pos[vx][vy];
					if(v == -1)
						continue;
					int msk2 = msk | s[v], tmp = dis[u] + w[v];
					if(tmp < f[msk2][v]) {
						f[msk2][v] = tmp;
						if(msk == msk2)
							Q.push(std::make_pair(-dis[v], v));
					}
				}
			}
		}
		for(int i = 0; i < tot; ++i)
			if(s[i]) {
				printf("%d\n", f[(1 << m) - 1][i]);
				break;
			}
	}
	return 0;
}
