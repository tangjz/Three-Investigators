#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define M 1000000007
#define all(a) a.begin(), a.end()

const long double eps = 1e-10 , pi = acos(-1.0);
inline int dcmp(long double x) {
	return (x > eps) - (x < -eps);
}

double ix, iy;
struct Point {
	long double x , y;
	Point (long double x = 0 , long double y = 0) : x(x) , y(y) {}
	void input() {
		scanf("%lf%lf",&ix,&iy);
		x = ix, y = iy;
	}
	bool operator < (const Point& R) const {
		if (dcmp(x - R.x) == 0)
			return dcmp(y - R.y) < 0;
		return dcmp(x - R.x) < 0;
	}
	bool operator == (const Point& R) const {
		return dcmp(x - R.x) == 0 && dcmp(y - R.y) == 0;
	}
	Point operator + (const Point& R) const {
		return Point(x + R.x , y + R.y);
	}
	Point operator - (const Point& R) const {
		return Point(x - R.x , y - R.y);
	}
	Point operator * (const long double& R) const {
		return Point(x * R , y * R);
	}
	Point operator / (const long double& R) const {
		return Point(x / R , y / R);
	}
	long double operator ^ (const Point& R) const {
		return x * R.y - y * R.x;
	}
	long double operator % (const Point& R) const {
		return x * R.x + y * R.y;
	}
	long double len() {
		return sqrt(*this % *this);
	}
	long double angle() {
		return atan2(y , x);
	}
}p[15], a[15];

struct Line {
	Point P , V; // P + Vt
	long double angle;
	Line () {}
	Line (Point A , Point B) {
		P = A , V = B - A;
		angle = atan2(V.y , V.x);
	}
	bool operator < (const Line& R) const {
		return angle < R.angle;
	}
	Point point(long double t) {
		return P + V * t;
	}
};
struct Circle {
    Point O;
    long double r;
    Circle () {}
    Circle (Point _O , long double _r) {
        O = _O , r = _r;
    }
    Point point(long double arc) {
        return Point(O.x + cos(arc) * r , O.y + sin(arc) * r);
    }
};
int n, r;

int getLineCircleIntersection(Line L , Circle C , long double& t1 , long double& t2) {
	long double a = L.V.x , b = L.P.x - C.O.x , c = L.V.y , d = L.P.y - C.O.y;
	long double e = a * a + c * c , f = 2 * (a * b + c * d);
	long double g = b * b + d * d - C.r * C.r;
	long double delta = f * f - 4 * e * g;
	if (dcmp(delta) < 0) return 0;
	if (dcmp(delta) == 0) {
		t1 = t2 = -f / (2 * e);
		return 1;
	}
	t1 = (-f - sqrt(delta)) / (e + e);
	t2 = (-f + sqrt(delta)) / (e + e);
	return 2;
}

/******?????????****/
long double sector_area(Point A , Point B , long double R) {
	long double theta = A.angle() - B.angle();
	while (theta < 0) theta += pi + pi;
	while (theta >= pi + pi) theta -= pi + pi;
	theta = min(theta , pi + pi - theta);
	return R * R * theta;
}//a[n] = a[0]
long double cal(long double x, long double y) {
	long double R = r;
	for(int i = 0; i < n; ++i)
		a[i] = p[i] - Point(x, y);
	a[n] = a[0];
	long double area = 0;
	for (int i = 0 ; i < n ; ++ i) {
		long double t1 = 0 , t2 = 0 , delta;
		Line L = Line(a[i] , a[i + 1]);
		int cnt = getLineCircleIntersection(L , Circle(Point(0 , 0) , R) , t1 , t2);
		Point X = L.point(t1) , Y = L.point(t2);
		bool f1 = dcmp(a[i].len() - R) <= 0 , f2 = dcmp(a[i + 1].len() - R) <= 0;
		if (f1 && f2)
			delta = fabs(a[i] ^ a[i + 1]);
		else if (!f1 && f2) {
			delta = sector_area(a[i] , X , R) + fabs(X ^ a[i + 1]);
		} else if (f1 && !f2) {
			delta = fabs(a[i] ^ Y) + sector_area(Y , a[i + 1] , R);
		} else {
			if (cnt > 1 && 0 < t1 && t1 < 1 && 0 < t2 && t2 < 1) {
				delta = sector_area(a[i] , X , R) + sector_area(Y , a[i + 1] , R) + fabs(X ^ Y);
			} else {
				delta = sector_area(a[i] , a[i + 1] , R);
			}
		}
		area += delta * dcmp(a[i] ^ a[i + 1]);
	}
	return area / 2;
}

long double work(long double x, long double yL, long double yR){
	for(int i = 0; i < n; ++i)
		if(dcmp(p[i].x - x) <= 0 && dcmp(p[(i + 1) % n].x - x) >= 0)
			yL = max(yL, (x - p[i].x) / (p[(i + 1) % n].x - p[i].x) * (p[(i + 1) % n].y - p[i].y) + p[i].y);
		else if(dcmp(p[i].x - x) >= 0 && dcmp(p[(i + 1) % n].x - x) <= 0)
			yR = min(yR, (x - p[i].x) / (p[(i + 1) % n].x - p[i].x) * (p[(i + 1) % n].y - p[i].y) + p[i].y);

	for(int i = 1; i <= 100; ++i){
		long double d1 = (2 * yL + yR) / 3, d2 = (yL + 2 * yR) / 3;
		long double area1 = cal(x, d1), area2 = cal(x, d2);
		if(area1 > area2) yR = d2;
		else yL = d1;
	}
	return cal(x, yL);
}

int main(){
	scanf("%d%d", &n, &r);
	long double xL = 100, xR = 0, yL = 100, yR = 0;
	for(int i = 0; i < n; ++i){
		p[i].input();
		xL = min(1. * p[i].x, xL);
		xR = max(1. * p[i].x, xR);
		yL = min(1. * p[i].y, yL);
		yR = max(1. * p[i].y, yR);
	}
	
	for(int i = 1; i <= 100; ++i){
		long double d1 = (2 * xL + xR) / 3, d2 = (xL + 2 * xR) / 3;
		long double area1 = work(d1, yL, yR), area2 = work(d2, yL, yR);
		if(area1 > area2) xR = d2;
		else xL = d1;
	}
	
	printf("%.8f\n", (double)work(xL, yL, yR));
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
