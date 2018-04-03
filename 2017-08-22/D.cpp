#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 1010;
const double eps = 1e-10;

inline int dcmp(double x){
	return (x > eps) - (x < -eps);
}

struct Point{
	double x, y;
	Point(double x = 0, double y = 0) : x(x), y(y) {}
	void input(){
		scanf("%lf%lf", &x, &y);
	}
	bool operator == (const Point &R) const{
		return dcmp(x - R.x) == 0 && dcmp(y - R.y) == 0;
	}
	Point operator * (const double &R) const{
		return Point(x * R, y * R);
	}
	Point operator - (const Point &R) const{
		return Point(x - R.x, y - R.y);
	}
	Point operator + (const Point &R) const{
		return Point(x + R.x, y + R.y);
	}
	double operator % (const Point &R) const{
		return x * R.x + y * R.y;
	}
	double operator ^ (const Point &R) const{
		return x * R.y - y * R.x;
	}
}p[maxn], V, P;

struct Line{
	Point P, V;
	double angle;
	Line(){}
	Line(Point A, Point B){
		P = A, V = B - A;
		angle = atan2(V.y, V.x);
	}
}line[maxn];
int n;
double k[maxn];

inline int Onleft(Point P, Point V, Point X){
	return dcmp(V ^ (X - P));
}

Point GetLineIntersection(Point P, Point v, Point Q, Point w){
	Point u = P - Q;
	double t1 = (w ^ u) / (v ^ w);
	return P + v * t1;
}

bool check(Line &line, Point &P, Point &V){
	return Onleft(P, V, line.P) <= 0 && Onleft(P, V, line.P + line.V) >= 0;
}

Point GetLineProjection(Point P , Point A , Point B) {
    Point v = B - A;
    return A + v * (v % (P - A) / (v % v));
}

int main(){
	while(~scanf("%d", &n)){
		for(int i = 0; i < n; ++i)
			p[i].input(), scanf("%lf", k + i);
		for(int i = 0; i < n; ++i){
			line[i] = Line(p[i], p[(i + 1) % n]);
		}
		P = Point(0, 0);
		V.input();
		double I = 0;
		int res = 0;
		while(I >= -4){
			res++;
			int i;
			for(i = 0; i < n; ++i)
				if(check(line[i], P, V)) break;
			Point NP = GetLineIntersection(P, V, line[i].P, line[i].V);
			if(NP == line[i].P || NP == line[i].P + line[i].V) break;
			Point PonSeg = GetLineProjection(P, line[i].P, line[i].P + line[i].V);
			Point PP = PonSeg * 2 - P;
			V = NP - PP;
			P = NP;
			if(dcmp(k[i]) != 0) I += log10(k[i]);
			else I = -1e9;
		}
		printf("%d\n", res);
	}
	
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
