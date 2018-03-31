#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
int t;
struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	LL det(Point const &t) const {
		return (LL)x * t.y - (LL)y * t.x;
	}
	LL dot(Point const &t) const {
		return (LL)x * t.x + (LL)y * t.y;
	}
} a[3], b[3], d1, d2;
pair<Point, Point> Lines[5];
bool onLeft(Point P, Point vec, Point Q) {
	return vec.det(Q - P) >= 0;
}
bool solve(Point a[3], Point b[3], Point vec) {
	int tot = 0;
	if(!vec.x && !vec.y) {
		if(!onLeft(a[0], a[1] - a[0], a[2]))
			swap(a[0], a[1]);
		Lines[tot++] = make_pair(a[0], a[1] - a[0]);
		Lines[tot++] = make_pair(a[1], a[2] - a[1]);
		Lines[tot++] = make_pair(a[2], a[0] - a[2]);
	} else {
		int L = 0, R = 0;
		for(int i = 1; i < 3; ++i) {
			if(vec.det(a[i] - a[L]) > 0)
				L = i;
			if(vec.det(a[i] - a[R]) < 0)
				R = i;
		}
		// printf("left %d %d\n", a[L].x, a[L].y);
		// printf("right %d %d\n", a[R].x, a[R].y);
		// Line 1: a[L] with -vec
		Lines[tot++] = make_pair(a[L], (Point){-vec.x, -vec.y});
		// Line 2: a[R] with vec
		Lines[tot++] = make_pair(a[R], vec);
		int x = 3 - L - R;
		if((a[x] - a[L]).det(a[R] - a[L]) > 0) {
			// Line 3 : a[L] with (a[x] - a[L])
			Lines[tot++] = make_pair(a[L], a[x] - a[L]);
			// Line 4 : a[x] with (a[R] - a[x])
			Lines[tot++] = make_pair(a[x], a[R] - a[x]);
		} else {
			// Line 3: a[L] with (a[R] - a[L])
			Lines[tot++] = make_pair(a[L], a[R] - a[L]);
		}
	}
	// printf("lines: %d\n", tot);
	// for(int i = 0; i < tot; ++i)
	//	printf("(%d, %d) + (%d, %d) t\n", Lines[i].first.x, Lines[i].first.y, Lines[i].second.x, Lines[i].second.y);
	for(int i = 0; i < 3; ++i) {
		bool chk = 1;
		for(int j = 0; j < tot && chk; ++j)
			chk &= onLeft(Lines[j].first, Lines[j].second, b[i]);
		if(chk)
			return 1;
	}
	return 0;
}
int sgn(LL x) {
	return (x > 0) - (x < 0);
}
bool has_intersection(Point A1, Point A2, Point B1, Point B2) {
	int sgn1 = sgn((A2 - A1).det(B1 - A1)), sgn2 = sgn((A2 - A1).det(B2 - A1));
	int sgn3 = sgn((B2 - B1).det(A1 - B1)), sgn4 = sgn((B2 - B1).det(A2 - B1));
	return sgn1 * sgn2 < 0 && sgn3 * sgn4 < 0;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		a[0].read(), a[1].read(), a[2].read(), d1.read();
		b[0].read(), b[1].read(), b[2].read(), d2.read();
		bool chk = 0;
		for(int i = 0; i < 3 && !chk; ++i)
			for(int j = 0; j < 3 && !chk; ++j)
				chk |= has_intersection(a[i], a[(i + 1) % 3], b[j], b[(j + 1) % 3]);
		printf("Case #%d: %s\n", Case, chk || solve(a, b, d1 - d2) || solve(b, a, d2 - d1) ? "YES" : "NO");
	}
	return 0;
}
