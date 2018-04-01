#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const double eps = 1e-8 , pi = acos(-1.0);
inline int dcmp(double x) {
    return (x > eps) - (x < -eps);
}

static int xx, yy;
struct Point {
    double x , y;
    Point (double x = 0 , double y = 0) : x(x) , y(y) {}
    void input() {
        scanf("%d%d",&xx,&yy);
				x = xx, y = yy;
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
    Point operator * (const double& R) const {
        return Point(x * R , y * R);
    }
    Point operator / (const double& R) const {
        return Point(x / R , y / R);
    }
    double operator ^ (const Point& R) const {
        return x * R.y - y * R.x;
    }
    double operator % (const Point& R) const {
        return x * R.x + y * R.y;
    }
    double len() {
        return sqrt(*this % *this);
    }
    double angle() {
        return atan2(y , x);
    }
}p[110];
// 两个向量的夹角，不分正负[0,pi)
double Angle(Point A , Point B) {
    return acos((A % B) / A.len() / B.len());
}
// 逆时针旋转
Point Rotate(Point A , double rad) {
    double Sin = sin(rad) , Cos = cos(rad);
    return Point(A.x * Cos - A.y * Sin , A.x * Sin + A.y * Cos);
}

int n;

int main(){
	int T, ca = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) p[i].input();
		double sum = 0;
		for(int i = 2; i < n; ++i){
			double area = p[i] ^ p[i + 1];
			sum += area;
		}
		double now = 0, ang = 0;
		for(int i = 2; i < n; ++i){
			double area = p[i] ^ p[i + 1];
			if(now + area >= sum / 2){
				Point l = p[i], r = p[i + 1];
				for(int j = 1; j <= 1000; ++j){
					Point d = (l + r) / 2;
					area = p[i] ^ d;
					if(now + area >= sum / 2) r = d;
					else l = d;
				}
				ang = r.angle();
				break;
			}
			now += area;
		}

		printf("Case %d:\n", ++ca);
		ang = 1.5 * pi - ang;
		for(int i = 1; i <= n; ++i){
			p[i] = Rotate(p[i], ang);
			if(dcmp(p[i].x) == 0) p[i].x = 0;
			if(dcmp(p[i].y) == 0) p[i].y = 0;
			printf("%.6f %.6f\n", p[i].x, p[i].y);
			//printf("%.6f %.6f\n", (double)(p[i].x + eps), (double)(p[i].y + eps));
		}
	}

	return 0;
}
