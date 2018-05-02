#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = 1001;
const DB pi = acos(-1.0), eps = 1e-14;
int t, n, L, m, ban;
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
struct Point {
	DB x, y;
	void read() {
		int _x, _y;
		scanf("%d%d", &_x, &_y);
		x = _x;
		y = _y;
	}
	bool operator < (Point const &t) const {
		int tp = sgn(x - t.x);
		return tp < 0 || (!tp && sgn(y - t.y) < 0);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y};
	}
	Point operator * (DB const &t) const {
		return (Point){t * x, t * y};
	}
	DB det(Point const &t) const {
		return x * t.y - y * t.x;
	}
	DB dot(Point const &t) const {
		return x * t.x + y * t.y;
	}
	DB len2() const {
		return dot(*this);
	}
} p[maxn], q[maxn];
Point LineLineIntersection(Point p1, Point p2, Point q1, Point q2) {
	return p1 + (p2 - p1) * ((q2 - q1).det(p1 - q1) / (p2 - p1).det(q2 - q1));
}
int CircleLineIntersection(Point o, DB r, Point p1, Point p2, Point &q1, Point &q2) {
	Point v = p2 - p1;
	Point p = LineLineIntersection(o, (Point){o.x + v.y, o.y - v.x}, p1, p2);
	int tp = sgn(r * r - (p - o).len2());
	if(tp < 0)
		return 0;
	if(tp == 0) {
		q1 = q2 = p;
		return 1;
	}
	DB k = sqrtl((r * r - (p - o).len2()) / (p2 - p1).len2());
	q1 = p - v * k;
	q2 = p + v * k;
	return 2;
}
struct Event {
	DB tim;
	int typ;
	bool operator < (Event const &t) const {
		int tp = sgn(tim - t.tim);
		return tp < 0 || (!tp && typ < t.typ);
	}
} e[maxn * 28 + 1];
bool addEvent(Point p1, Point p2) { // L <= |p|, |q| <= sqrt(3) L
	DB u1 = atan2(p1.y, p1.x), v1 = asin(sqrtl(3LL * L * L / p1.len2() / 4)) - pi / 6;
	DB u2 = atan2(p2.y, p2.x), v2 = asin(sqrtl(3LL * L * L / p2.len2() / 4)) - pi / 6;
	if(sgn(u1 - u2) < 0) {
		swap(u1, u2);
		swap(v1, v2);
	}
	if(sgn(u1 - u2 - pi) > 0) {
		u2 += pi * 2;
		swap(u1, u2);
		swap(v1, v2);
	}
	DB L = max(u1 - v1, u2 - v2), R = min(u1 + v1, u2 + v2);
	if(sgn(L - R) > 0)
		return 0;
//	printf("(%.4f, %.4f) -> (%.4f, %.4f): [%.10f, %.10f]\n", p1.x, p1.y, p2.x, p2.y, L, R);
	if(sgn(R) < 0) {
		L += pi * 2;
		R += pi * 2;
	}
	bool vis = 0;
	for(int i = 0; i < 6; ++i, L += pi / 3, R += pi / 3) {
		if(sgn(R - pi * 2) >= 0) {
			L -= pi * 2;
			R -= pi * 2;
		}
		if(sgn(L) <= 0) {
			vis = 1;
			e[m++] = (Event){R, 1};
			e[m++] = (Event){L + pi * 2, -1};
		} else {
			e[m++] = (Event){L, -1};
			e[m++] = (Event){R, 1};
		}
	}
	ban += !vis;
	return 1;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &m, &L);
		bool chk = 1;
		for(int i = 0; chk && i < m; ++i) {
			q[i].read();
			chk &= sgn(q[i].len2() - 3LL * L * L) <= 0;
		}
		if(!chk) {
			puts("Change");
			continue;
		}
		sort(q, q + m);
		n = 0;
		for(int i = 0; i < m; ++i) {
			for( ; n > 1 && sgn((p[n - 1] - p[n - 2]).det(q[i] - p[n - 2])) <= 0; --n);
			p[n++] = q[i];
		}
		for(int i = m - 1, tp = n; i >= 0; --i) {
			for( ; n > tp && sgn((p[n - 1] - p[n - 2]).det(q[i] - p[n - 2])) <= 0; --n);
			p[n++] = q[i];
		}
		n -= n > 1;
		m = ban = 0;
		for(int i = n - 1, j = 0, si = sgn(p[i].len2() - 1LL * L * L), sj; chk && j < n; i = j++, si = sj) {
			sj = sgn(p[j].len2() - 1LL * L * L);
			if(si <= 0 && sj <= 0)
				continue;
			Point p1, p2;
			int cnt = CircleLineIntersection((Point){0, 0}, L, p[i], p[j], p1, p2);
			if(cnt == 2 && sgn((p2 - p1).dot(p[j] - p[i])) < 0)
				swap(p1, p2);
			if(cnt == 2 && sgn((p2 - p[i]).dot(p2 - p[j])) > 0)
				--cnt;
			if(cnt >= 1 && sgn((p1 - p[i]).dot(p1 - p[j])) > 0) {
				p1 = p2;
				--cnt;
			}
			if(cnt <= 1) {
				chk &= addEvent(si < 0 ? p1 : p[i], sj < 0 ? p1 : p[j]);
			} else {
				if(si > 0)
					chk &= addEvent(p[i], p1);
				if(sj > 0)
					chk &= addEvent(p2, p[j]);
			}
		}
		if(!chk) {
			puts("Change");
			continue;
		}
		chk = !ban;
		sort(e, e + m);
		for(int i = 0; !chk && i < m; ++i) {
			ban += e[i].typ;
			chk |= !ban;
		}
		puts(chk ? "Cast" : "Change");
	}
	return 0;
}
