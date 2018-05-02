#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const DB eps = 1e-9;
int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
bool readDB(DB &x) {
	double tp;
	if(scanf("%lf", &tp) != 1)
		return 0;
	x = tp;
	return 1;
}
void writeDB(DB x, char endc = '\n') {
	printf("%.4f%c", sgn(x) ? (double)x : 0.0, endc);
}
struct Point {
	DB x, y;
	bool read() {
		return readDB(x) && readDB(y);
	}
	bool operator == (Point const &t) const {
		return !sgn(x - t.x) && !(y - t.y);
	}
	bool operator < (Point const &t) const {
		int tp = sgn(x - t.x);
		return tp < 0 || (!tp && sgn(y - t.y) < 0);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	Point operator * (DB const &t) const {
		return (Point){x * t, y * t};
	}
	DB det(Point const &t) const {
		return x * t.y - y * t.x;
	}
	DB dot(Point const &t) const {
		return x * t.x + y * t.y;
	}
} ;
struct Line {
	Point u, v;
	bool operator < (Line const &t) const {
		return u < t.u || (u == t.u && v < t.v);
	}
	bool read() {
		return u.read() && v.read();
	}
	void write() {
		writeDB(u.x, ' ');
		writeDB(u.y, ' ');
		writeDB(v.x, ' ');
		writeDB(v.y);
	}
	Point intersection(Line const &t) const {
		return u - (u - v) * ((t.v - t.u).det(u - t.u) / (v - u).det(t.v - t.u));
	}
} ;
int tot;
Point pL, pR, qL, qR, seq[11];
Line cur, seg[9];
vector<Line> out;
int main() {
	pL.read();
	pR.read();
	qL.read();
	qR.read();
	seg[0] = (Line){(Point){pL.x, pL.y}, (Point){pL.x, pR.y}};
	seg[1] = (Line){(Point){pL.x, pR.y}, (Point){pR.x, pR.y}};
	seg[2] = (Line){(Point){pR.x, pR.y}, (Point){pR.x, pL.y}};
	seg[3] = (Line){(Point){pR.x, pL.y}, (Point){pL.x, pL.y}};
	seg[4] = (Line){(Point){qL.x, qL.y}, (Point){qL.x, qR.y}};
	seg[5] = (Line){(Point){qL.x, qR.y}, (Point){qR.x, qR.y}};
	seg[6] = (Line){(Point){qR.x, qR.y}, (Point){qR.x, qL.y}};
	seg[7] = (Line){(Point){qR.x, qL.y}, (Point){qL.x, qL.y}};
	while(cur.read()) {
		tot = 0;
		seq[tot++] = cur.u;
		seq[tot++] = cur.v;
		for(int i = 0; i < 8; ++i)
			if(sgn((cur.v - cur.u).det(seg[i].v - seg[i].u))) {
				Point tp = cur.intersection(seg[i]);
				if(sgn((tp - seg[i].u).dot(tp - seg[i].v)) <= 0)
					seq[tot++] = tp;
			} else if(!sgn((cur.v - cur.u).det(seg[i].u - cur.u))) {
				seq[tot++] = seg[i].u;
				seq[tot++] = seg[i].v;
			}
		sort(seq, seq + tot);
		tot = unique(seq, seq + tot) - seq;
		for(int i = 1, chk = 0; i < tot; ++i) {
			Point lft = seq[i - 1], rht = seq[i];
			chk ^= (cur.u == lft) ^ (cur.v == lft);
			if(!chk)
				continue;
			Point mid = (Point){(lft.x + rht.x) / 2, (lft.y + rht.y) / 2};
			bool chk1 = sgn(pL.x - mid.x) < 0 && sgn(mid.x - pR.x) < 0
				&& sgn(pL.y - mid.y) < 0 && sgn(mid.y - pR.y) < 0;
			bool chk2 = sgn(qL.x - mid.x) <= 0 && sgn(mid.x - qR.x) <= 0
				&& sgn(qL.y - mid.y) <= 0 && sgn(mid.y - qR.y) <= 0;
			if(chk1 && !chk2)
				out.push_back((Line){lft, rht});
		}
	}
	sort(out.begin(), out.end());
	reverse(out.begin(), out.end());
	for(Line item : out)
		item.write();
	return 0;
}
