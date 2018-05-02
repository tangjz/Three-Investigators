#include <bits/stdc++.h>
using namespace std;
const int maxn = 11, maxm = 101, BLEN = 3, BMSK = 7, dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
int n, m, q, need[2], bit[maxn], rem[2][maxm];
char buf[maxn][maxn], mat[maxn][maxn];
struct State {
	int cnt[2], msk;
	bool operator < (State const &t) const {
		if(cnt[0] != t.cnt[0])
			return cnt[0] < t.cnt[0];
		if(cnt[1] != t.cnt[1])
			return cnt[1] < t.cnt[1];
		return msk < t.msk;
	}
	void canonicalize() {
		int tot = 0, pos[maxn] = {};
		for(int i = 0; i < m; ++i) {
			int pre = (msk >> bit[i]) & BMSK;
			int cur = !pre ? 0 : (pos[pre] ? pos[pre] : (pos[pre] = ++tot));
			msk ^= (pre ^ cur) << bit[i];
		}
	}
	bool connected() const {
		int idx = 0;
		for(int i = 0; i < m; ++i) {
			int cur = (msk >> bit[i]) & BMSK;
			if(cur) {
				if(idx && idx != cur)
					return 0;
				idx = cur;
			}
		}
		return 1;
	}
	bool extend(int pos, bool adt) {
		int idx = (msk >> bit[pos]) & BMSK;
		if(idx) {
			int cnt = adt;
			for(int i = 0; i < m; ++i)
				cnt += ((msk >> bit[i]) & BMSK) == idx;
			if(cnt == 1)
				return 0;
		} else {
			for(int i = 0; i < m; ++i)
				idx = max(idx, (msk >> bit[i]) & BMSK);
			if(adt)
				msk ^= (++idx) << bit[pos];
		}
		if(!adt) {
			msk ^= msk & (BMSK << bit[pos]);
		} else if(pos) {
			int lft = (msk >> bit[pos - 1]) & BMSK;
			if(lft) {
				for(int i = 0; i < m; ++i)
					if(((msk >> bit[i]) & BMSK) == lft)
						msk ^= (lft ^ idx) << bit[i];
			}
		}
		canonicalize();
		return 1;
	}
} ;
set<State> vis[maxm]; // visited but failed
bool dfs(int dep, State cur) {
	if(cur.cnt[0] == need[0] && cur.cnt[1] == need[1])
		return cur.connected();
	if(dep == n * m || cur.cnt[0] + rem[0][dep] < need[0] || cur.cnt[1] + rem[1][dep] < need[1] || vis[dep].count(cur))
		return 0;
	vis[dep].insert(cur);
	int x = dep / m, y = dep % m;
	State nxt = cur;
	if(nxt.extend(y, 0) && dfs(dep + 1, nxt)) {
		mat[x][y] = '.';
		return 1;
	}
	nxt = cur;
	nxt.cnt[0] += mat[x][y] == 'W';
	nxt.cnt[1] += mat[x][y] == 'B';
	if(mat[x][y] != '.' && nxt.extend(y, 1) && dfs(dep + 1, nxt)) {
		mat[x][y] = "OX"[mat[x][y] == 'B'];
		return 1;
	}
	return 0;
}
int main() {
	for(int i = 1; i < maxn; ++i)
		bit[i] = bit[i - 1] + BLEN;
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			buf[i][j] = "WB"[(i & 1) ^ (j & 1)];
	while(q--) {
		int x, y;
		scanf("%d%d", &x, &y);
		buf[--x][--y] = '.';
	}
	scanf("%d%d", need + 0, need + 1);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) {
			if(buf[i][j] == '.')
				continue;
			for(int x = 0; x < n; ++x)
				for(int y = 0; y < m; ++y)
					mat[x][y] = '.';
			int fir = i * m + j, las = fir, sz = 0, cnt[2] = {};
			static int que[maxm];
			que[sz++] = fir;
			swap(buf[i][j], mat[i][j]);
			++cnt[mat[i][j] == 'B'];
			for(int k = 0; k < sz; ++k) {
				int u = que[k], x = u / m, y = u % m;
				for(int o = 0; o < 4; ++o) {
					int xx = x + dx[o], yy = y + dy[o];
					if(xx >= 0 && xx < n && yy >= 0 && yy < m && buf[xx][yy] != '.') {
						int v = que[sz++] = xx * m + yy;
						swap(buf[xx][yy], mat[xx][yy]);
						++cnt[mat[xx][yy] == 'B'];
						las = max(las, v);
					}
				}
			}
			if(cnt[0] < need[0] || cnt[1] < need[1])
				continue;
			rem[0][las + 1] = rem[1][las + 1] = 0;
			set<State>().swap(vis[las + 1]);
			for(int i = las; i >= fir; --i) {
				int x = i / m, y = i % m;
				rem[0][i] = rem[0][i + 1] + (mat[x][y] == 'W');
				rem[1][i] = rem[1][i + 1] + (mat[x][y] == 'B');
				set<State>().swap(vis[i]);
			}
			if(!dfs(fir, (State){{0, 0}, 0}))
				continue;
			for(int x = 0; x < n; ++x) {
				for(int y = 0; y < m; ++y)
					if(mat[x][y] == 'W' || mat[x][y] == 'B')
						mat[x][y] = '.';
				mat[x][m] = '\0';
				puts(mat[x]);
			}
			return 0;
		}
	puts(":-(");
	return 0;
}
