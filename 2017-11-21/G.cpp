#include <bits/stdc++.h>
using namespace std;
const int maxn = 1001, maxs = 101;
void readDB(int &x, int prec = 2) {
	char buf[11];
	scanf("%s", buf);
	x = 0;
	for(int i = 0, chk = 0; buf[i]; ++i)
		if(buf[i] == '.') {
			chk = 1;
		} else {
			x = x * 10 + buf[i] - '0';
			prec -= chk;
		}
	for( ; prec--; x *= 10);
}
int sgn(int x) {
	return (x > 0) - (x < 0);
}
struct Point {
	int x, y;
	void read() {
		readDB(x);
		readDB(y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	int det(Point const &t) const {
		return x * t.y - y * t.x;
	}
	int dot(Point const &t) const {
		return x * t.x + y * t.y;
	}
} p[3];
bool inner(Point q) {
	int v1 = sgn((p[1] - p[0]).det(q - p[0]));
	int v2 = sgn((p[2] - p[1]).det(q - p[1]));
	int v3 = sgn((p[0] - p[2]).det(q - p[2]));
	return v1 && v1 == v2 && v2 == v3;
}
bool ins(Point a1, Point a2, Point b1, Point b2) {
	int v1 = sgn((a2 - a1).det(b1 - a1));
	int v2 = sgn((a2 - a1).det(b2 - a1));
	int v3 = sgn((b2 - b1).det(a1 - b1));
	int v4 = sgn((b2 - b1).det(a2 - b1));
	return v1 * v2 < 0 && v3 * v4 < 0;
}
bool onSeg(Point q, Point a1, Point a2) {
	return !sgn((a1 - q).det(a2 - q)) && sgn((a1 - q).dot(a2 - q)) <= 0;
}
bool check(Point u, Point v) {
	if(ins(p[0], p[1], u, v) || ins(p[1], p[2], u, v) || ins(p[2], p[0], u, v) || inner((Point){(u.x + v.x) >> 1, (u.y + v.y) >> 1}))
		return 1;
	for(int i = 0; i < 3; ++i) {
		if(!onSeg(p[i], u, v))
			continue;
		int j = !i, k = 3 - i - j;
		if(onSeg(u, p[j], p[k]) || onSeg(v, p[j], p[k]))
			return 1;
	}
	return 0;
}
int n, que[maxn], dis[maxn];
bool ban[maxn];
char buf[maxs];
inline int idx(int x, int y) {
	return x * n + y;
}
inline void rdx(int o, int &x, int &y) {
	x = o / n;
	y = o % n;
}
int main() {
	while(scanf("%d", &n) == 1) {
		for(int i = 0; i < 3; ++i)
			p[i].read();
		for(int j = n - 1; j >= 0; --j) {
			scanf("%s", buf);
			for(int i = 0; i < n; ++i)
				ban[idx(i, j)] = buf[i] == '#' || inner((Point){i * 100, j * 100});
		}
		if(ban[idx(0, 0)] || ban[idx(n - 1, n - 1)]) {
			puts("-1");
			continue;
		}
		int L = 0, R = 0;
		memset(dis, -1, sizeof dis);
		dis[idx(0, 0)] = 0;
		que[R++] = idx(0, 0);
		while(L < R) {
			int u = que[L++], ux, uy;
			rdx(u, ux, uy);
			for(int dx = -1; dx <= 1; ++dx) {
				int vx = ux + dx;
				if(vx < 0 || vx >= n)
					continue;
				for(int dy = -1; dy <= 1; ++dy) {
					int vy = uy + dy;
					if(vy < 0 || vy >= n)
						continue;
					int v = idx(vx, vy);
					if(!ban[v] && dis[v] == -1 && !check((Point){ux * 100, uy * 100}, (Point){vx * 100, vy * 100})) {
						dis[v] = dis[u] + 1;
						que[R++] = v;
					}
				}
			}
		}
		printf("%d\n", dis[idx(n - 1, n - 1)]);
	}
	return 0;
}
