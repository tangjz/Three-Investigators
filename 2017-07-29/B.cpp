#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const double pi = acos(-1.0), eps = 1e-9;
const int maxn = 60;
const int maxm = 100000;
int n, m;
int tot;

inline int dcmp(double x){
	return (x > eps) - (x < -eps);
}
struct Point{
	double x, y;
	Point(double x = 0, double y = 0) : x(x),y(y) {}
	void input(){
		scanf("%lf%lf", &x, &y);
	}
	double operator % (const Point &R) const{
		return x * R.x + y * R.y;
	}
	double operator ^ (const Point &R) const{
		return x * R.y - y * R.x;
	}
	double len(){
		return sqrt(*this % *this);
	}
	Point operator - (const Point &R) const{
		return Point(x - R.x, y - R.y);
	}
	bool operator < (const Point &R) const{
		return dcmp(x - R.x) < 0 || (dcmp(x - R.x) == 0 && dcmp(y - R.y) < 0);
	}
	double angle(){
		return atan2(y, x);
	}
}p[maxm], s[maxm];

struct Circle{
	Point O;
	double r;
	void input(){
		O.input(); scanf("%lf", &r);
	}
	Point point(double arc){
		return Point(O.x + cos(arc) * r, O.y + sin(arc) * r);
	}
}cir[maxn];

void getTangets(Circle A, Circle B){
	if(A.r < B.r) swap(A, B);
	double dist = (A.O - B.O).len(), dr = A.r - B.r;
	double ang = acos(dr / dist);
	double base = (B.O - A.O).angle();
	p[++tot] = A.point(base + ang);
	p[++tot] = B.point(base + ang);
	p[++tot] = A.point(base - ang);
	p[++tot] = B.point(base - ang);
}

void getTangets(Point P, Circle C){
	Point u = P - C.O;
	double dist = u.len();
	if(dcmp(dist - C.r) == 0) return;
	double ang = acos(C.r / dist);
	double ang2 = atan2(u.y, u.x);
	p[++tot] = C.point(ang2 + ang);
	p[++tot] = C.point(ang2 - ang);
}

inline int Onleft(Point P, Point A, Point B){
	return dcmp((B - A) ^ (P - A));
}

bool inCir(Point P, Circle C){
	Point u = P - C.O;
	double dist = u.len();
	return dcmp(dist - C.r) == 0;
}

int main(){
	while(~scanf("%d%d", &n, &m)){
		tot = 0;
		for(int i = 1; i <= n; ++i){
			cir[i].input();
			for(int j = 1; j < i; ++j){
				getTangets(cir[i], cir[j]);
			}
		}
		for(int i = 1; i <= m; ++i){
			for(int j = 1; j <= 3; ++j){
				Point po; po.input();
				p[++tot] = po;
				for(int k = 1; k <= n; ++k){
					getTangets(po, cir[k]);
				}
			}
		}
		if(n == 1 && !m){
			printf("%.10lf\n", cir[1].r * pi * 2);
			continue;
		}
		
		sort(p + 1, p + tot + 1);
		int top = 0;
		for(int i = 1; i <= tot; ++i){
			while(top > 1 && Onleft(p[i], s[top - 2], s[top - 1]) <= 0) --top;
			s[top++] = p[i];
		}
		int tmp = top;
		for(int i = tot - 1; i; --i){
			while(top > tmp && Onleft(p[i], s[top - 2], s[top - 1]) <= 0) --top;
			s[top++] = p[i];
		}
		
		double ans = 0;
		for(int i = 0; i < top - 1; ++i){
			int l = i, r = (i + 1) % top;
			ans += (s[r] - s[l]).len();
			for(int j = 1; j <= n; ++j){
				if(inCir(s[l], cir[j]) && inCir(s[r], cir[j])){
					ans -= (s[r] - s[l]).len();
					Point u = s[l] - cir[j].O, v = s[r] - cir[j].O;
					//printf("%.10f\n", max(-1.0, (u % v) / u.len() / v.len()));
					double ang = acos(min(1.0, max(-1.0, (u % v) / u.len() / v.len())));
					if(Onleft(s[l], s[r], cir[j].O) >= 0) ans += cir[j].r * ang;
					else ans += cir[j].r * (2 * pi - ang);
				}
			}
		}
		
		printf("%lf\n", ans);
	}
	
	return 0;
}
