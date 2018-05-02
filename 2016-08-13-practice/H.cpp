#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e5 + 1;
int n, m, sz, ord[maxn];
LL ans[maxn];
struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
	bool operator < (Point const &t) const {
		return x < t.x || (x == t.x && y < t.y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	LL dot(Point const &t) const {
		return (LL)x * t.x + (LL)y * t.y;
	}
	LL det(Point const &t) const {
		return (LL)x * t.y - (LL)y * t.x;
	}
} p[maxn], q[maxn], stk[maxn];
bool polarOrder(int const &u, int const &v) { // at one half plane
	return p[u].det(p[v]) > 0;
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		p[i].read();
		ord[i] = i;
	}
	sort(ord, ord + n, polarOrder);
	scanf("%d", &m);
	for(int i = 0; i < m; ++i)
		q[i].read();
	sort(q, q + m);
	for(int i = 0; i < m; ++i) {
		for( ; sz > 1 && (stk[sz - 1] - stk[sz - 2]).det(q[i] - stk[sz - 2]) <= 0; --sz);
		stk[sz++] = q[i];
	}
	for(int i = 0, j = 0; i < n; ++i) {
		int o = ord[i];
		ans[o] = p[o].dot(stk[j]);
		while(j + 1 < sz) {
			LL tp = p[o].dot(stk[j + 1]);
			if(ans[o] <= tp)
				break;
			ans[o] = tp;
			++j;
		}
	}
	for(int i = 0; i < n; ++i)
		printf("%lld%c", ans[i], " \n"[i == n - 1]);
	return 0;
}
