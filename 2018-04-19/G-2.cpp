#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = (int)2e3 + 5, INF = (int)1e4 + 5;
const DB eps = 1e-7;
int sgn(double x) {
	return (x > eps) - (x < -eps);
}
struct Point {
	DB x, y;
	void read() {
		int x, y;
		scanf("%d%d", &x, &y);
		this -> x = x;
		this -> y = y;
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y};
	}
	Point operator * (DB const &t) const {
		return (Point){x * t, y * t};
	}
	DB dot(Point const &t) const {
		return x * t.x + y * t.y;
	}
	DB det(Point const &t) const {
		return x * t.y - y * t.x;
	}
	DB len() const {
		return sqrtl(dot(*this));
	}
	int site() const {
		int sx = sgn(x), sy = sgn(y);
		return !sx && !sy ? 0 :
			sx > 0 && sy >= 0 ? 1 :
			sx <= 0 && sy > 0 ? 2 :
			sx < 0 && sy <= 0 ? 3 : 4;
	}
	bool operator < (Point const &t) const {
		int sL = site(), sR = t.site();
		if(sL != sR)
			return sL < sR;
		return sgn(det(t)) > 0;
	}
} ;
struct Line {
	Point o, v;
	bool operator < (Line const &t) const {
		return v < t.v;
	}
	bool parallel(Line const &t) const {
		return !sgn(v.det(t.v));
	}
	bool onLeft(Point const &t) const {
		return sgn(v.det(t - o)) > 0;
	}
	bool onSegment(Point const &t) const {
		return !sgn(v.det(t - o)) && sgn((o - t).dot(o + v - t)) <= 0;
	}
	Point intersection(Line const &t) const {
		Point dt = o - t.o;
		DB coeff = t.v.det(dt) / v.det(t.v);
		return o + v * coeff;
	}
} ;
int n;
Point a[maxn], p[maxn];
Line b[maxn], q[maxn];
DB ans;
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		a[i].read();
	for(int i = 0; i < n; ++i) {
		int tot = 0;
		b[tot++] = (Line){(Point){-INF, -INF}, (Point){INF * 2, 0}};
		b[tot++] = (Line){(Point){INF, -INF}, (Point){0, INF * 2}};
		b[tot++] = (Line){(Point){INF, INF}, (Point){-INF * 2, 0}};
		b[tot++] = (Line){(Point){-INF, INF}, (Point){0, -INF * 2}};
		for(int j = 0; j < n; ++j) {
			if(i == j)
				continue;
			b[tot].o = (a[i] + a[j]) * 0.5;
			b[tot].v = a[j] - a[i];
			swap(b[tot].v.x, b[tot].v.y);
			b[tot].v.x = -b[tot].v.x;
			++tot;
		}
		sort(b, b + tot);
		int L = 0, R = 0;
		q[0] = b[0];
		for(int j = 1; j < tot; ++j) {
			for( ; L < R && !b[j].onLeft(p[R - 1]); --R);
			for( ; L < R && !b[j].onLeft(p[L]); ++L);
			if(sgn(q[R].v.det(b[j].v))) {
				q[++R] = b[j];
			} else if(q[R].onLeft(b[j].o)) {
				q[R] = b[j];
			}
			if(L < R) {
				p[R - 1] = q[R - 1].intersection(q[R]);
			}
		}
		for( ; L < R && !q[L].onLeft(p[R - 1]); --R);
		p[R] = q[R].intersection(q[L]);
		for(int j = L; j <= R; ++j) {
			int jj = j > L ? j - 1 : R;
			Line qq = (Line){p[jj], p[j] - p[jj]};
			for(int k = 0; k < n; ++k) {
				int kk = k ? k - 1 : n - 1;
				Line cur = (Line){a[kk], a[k] - a[kk]};
				if(qq.parallel(cur))
					continue;
				Point ins = qq.intersection(cur);
				if(qq.onSegment(ins) && cur.onSegment(ins)) {
					ans = max(ans, (ins - a[i]).len());
				}
			}
		}
		for(int j = L; j <= R; ++j) {
			int ctr = 0;
			for(int k = 0; k < n; ++k) {
				int kk = k ? k - 1 : n - 1;
				Line cur = (Line){a[kk], a[k] - a[kk]};
				if(cur.onSegment(p[j])) {
					ctr = -1;
					break;
				}
				int s0 = sgn(cur.v.det(p[j] - a[kk]));
				int s1 = sgn(a[kk].y - p[j].y);
				int s2 = sgn(a[k].y - p[j].y);
				ctr += s0 > 0 && s1 <= 0 && s2 > 0;
				ctr -= s0 < 0 && s1 > 0 && s2 <= 0;
			}
			if(ctr != 0) {
				ans = max(ans, (p[j] - a[i]).len());
			}
		}
	}
	printf("%.20f\n", (double)ans);
	return 0;
}
