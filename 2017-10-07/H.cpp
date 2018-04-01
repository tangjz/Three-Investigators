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

const long double eps = 1e-6, pi = acos(-1.0);
inline int dcmp(long double x){
	return (x > eps) - (x < -eps);
}

double xxx, yyy;
struct Point{
	long double x, y;
	Point(long double x = 0, long double y = 0) : x(x), y(y) {}
	void input(){
		scanf("%lf%lf", &xxx, &yyy);
		x = xxx, y = yyy;
	}
	Point operator - (const Point &R) const{
		return Point(x - R.x, y - R.y);
	}
	bool operator < (const Point &R) const{
		if(dcmp(x - R.x) == 0) return dcmp(y - R.y) < 0;
		else return dcmp(x - R.x) < 0;
	}
	long double operator ^ (const Point &R) const{
		return x * R.y - y * R.x;
	}
	bool operator == (const Point &R) const{
		return dcmp(x - R.x) == 0 && dcmp(y - R.y) == 0;
	}
}a[9], b[9], tim;
int p[9];
int n;
bool bre[9];

bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2){
	long double c1 = (a2 - a1) ^ (b1 - a1);
	long double c2 = (a2 - a1) ^ (b2 - a1);
	if(c1 == 0 && c2 == 0){
		if(a2 < a1) swap(a1, a2);
		if(b2 < b1) swap(b1, b2);
		return max(a1, b1) < min(a2, b2) || max(a1, b1) == min(a2, b2);
	}
	long double c3 = (b2 - b1) ^ (a1 - b1);
	long double c4 = (b2 - b1) ^ (a2 - b1);
	return dcmp(c1) * dcmp(c2) <= 0 && dcmp(c3) * dcmp(c4) <= 0;
}

void work(int len){
	Point vt = tim;
	for(int i = len - 1; i >= 0; --i){
		if(dcmp(a[p[i]].x - b[p[i]].x) == 0)
			vt.x = 2 * a[p[i]].x - vt.x;
		else
			vt.y = 2 * a[p[i]].y - vt.y;				
	}
	if(vt == Point(0, 0)) return;
	memset(bre, 0, sizeof(bre));
	
	long double x = 0, y = 0;
	long double theta = atan2(vt.y, vt.x);
	if(theta < -pi) theta += 2 * pi;
	if(theta > pi) theta -= 2 * pi;
	for(int i = 0; i < len; ++i){
		long double nx, ny;
		if(dcmp(a[p[i]].x - b[p[i]].x) == 0){
			if(dcmp(x - a[p[i]].x) == 0) return;
			if(x < a[p[i]].x){
				if(dcmp(fabs(theta) - pi / 2) >= 0) return;
			}else{
				if(dcmp(fabs(theta) - pi / 2) <= 0) return;
			}
			nx = a[p[i]].x, ny = y + (a[p[i]].x - x) * tan(theta);
			if(dcmp(ny - a[p[i]].y) < 0 || dcmp(ny - b[p[i]].y) > 0) return;
			if(theta > 0) theta = pi - theta;
			else theta = -pi - theta;
		}else{
			if(dcmp(y - a[p[i]].y) == 0) return;
			if(y < a[p[i]].y){
				if(dcmp(theta) <= 0 || dcmp(theta - pi) == 0) return;
			}else{
				if(dcmp(theta) >= 0 || dcmp(theta - pi) == 0) return;
			}
			nx = x + (a[p[i]].y - y) / tan(theta), ny = a[p[i]].y;
			if(dcmp(nx - a[p[i]].x) < 0 || dcmp(nx - b[p[i]].x) > 0) return;
			theta = -theta;
		}
		if(theta < -pi) theta += 2 * pi;
		if(theta > pi) theta -= 2 * pi;
		bre[p[i]] = 1;
		for(int j = 0; j < n; ++j)
			if(!bre[j] && SegmentProperIntersection(a[j], b[j], Point(x, y), Point(nx, ny))) return;
		x = nx, y = ny;
	}
	
	for(int i = 0; i < n; ++i)
		if(!bre[i] && SegmentProperIntersection(a[i], b[i], Point(x, y), tim)) return;
	
	if(dcmp(atan2(tim.y - y, tim.x - x) - theta) == 0 || dcmp(atan2(tim.y - y, tim.x - x) - theta + 2 * pi) == 0 ||
		dcmp(atan2(tim.y - y, tim.x - x) - theta - 2 * pi) == 0);
	else return;
	printf("%d\n", len);
	//for(int i = 0; i < len; ++i) printf("%d ", p[i]); printf("\n");
	exit(0);
}

int main(){
	scanf("%d", &n);
	tim.input();
	for(int i = 0; i < n; ++i){
		a[i].input();
		b[i].input();
		if(b[i] < a[i]) swap(a[i], b[i]);
	}
	
	for(int i = n; i >= 1; --i){
		for(int j = 0; j < n; ++j) p[j] = j;
		do{
			work(i);
		}while(next_permutation(p, p + n));
	}
	work(0);
 	puts("impossible");
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}

