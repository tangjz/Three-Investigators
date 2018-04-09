#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 210;
const long double eps = 1e-12;

struct Point
{
	long double x;
	long double y;
	int type;
	int value;
	bool operator<(const Point &v)
	const{
		if(fabs(x - v.x) < eps)
			return y + eps < v.y;
		return x + eps < v.x;
	};

	Point operator-(const Point &v)
	const{
		return (Point){x - v.x, y - v.y, 0, 0};
	}
};

inline long double cross(const Point &u, const Point &v)
{
	return u.x * v.y - u.y * v.x;
}

struct Line
{
	Point l;
	Point r;
	int side(const Point &u, const Point &v)
	const{
		long double delta = cross(v - u, r - l);
		if(fabs(delta) < eps)
			return 0;
		return delta < -eps?-1:1;
	};
	int side(const Point &u)
	const{
		long double delta = cross(u - l, r - l);
		if(fabs(delta) < eps)
			return 0;
		return delta < -eps?-1:1;
	};
};

int N;
long double ans;
Point poly[NMAX];
Line line;
vector<Point> intern;

void internLine(const Line &line, const Line &seg)
{
	if(fabs(cross(line.r - line.l, seg.r - seg.l)) < eps
		|| line.side(seg.l) * line.side(seg.r) > -eps)
		return;
	long double a = cross(line.l, line.r), b = cross(seg.l, seg.r), d = cross(line.l - line.r, seg.l - seg.r);
	intern.push_back((Point){(a * (seg.l.x - seg.r.x) - b * (line.l.x - line.r.x)) / d, (a * (seg.l.y - seg.r.y) - b * (line.l.y - line.r.y)) / d, 1, 0});
}

inline long double sqr(const long double &x)
{
	return x * x;
}

inline long double dist(const Point &u, const Point &v)
{
	return sqrt(sqr(u.x - v.x) + sqr(u.y - v.y));
}

int main()
{
	int i, j, k, x, y;
	int cur, res, cnt, s1, s2;
	long double tmp;
	scanf("%d", &N);
	for(i = 0;i < N;i += 1)
	{
		scanf("%d %d", &x, &y);
		poly[i].x = x;
		poly[i].y = y;
	}
	for(i = 0;i < N;i += 1)
	{
		for(j = 0;j < i;j += 1)
		{
			line = (Line){poly[i], poly[j]};
			intern.erase(intern.begin(), intern.end());
			for(k = 0;k < N;k += 1)
			{
				internLine(line, (Line){poly[k], poly[(k + 1) % N]});
				if(!line.side(poly[k])
					&& (res = -(s1 = line.side(poly[k], poly[(k + 1) % N])) * (s2 = line.side(poly[k], poly[(k - 1 + N) % N]))) >= 0)
					intern.push_back((Point){poly[k].x, poly[k].y, res, s1 + s2});
			}
			sort(intern.begin(), intern.end());
			for(tmp = cur = cnt = k = 0;k + 1 < intern.size();k += 1)
			{
				cur ^= intern[k].type;
				if(!intern[k].type)
					cnt += 1;
				if(!(cnt & 1) && k && !intern[k - 1].type && intern[k - 1].value * intern[k].value < 0)
					cur ^= 1;
				if(!cur)
					tmp = 0.0;
				if(cur || (cnt & 1))
					tmp += dist(intern[k], intern[k + 1]);
				ans = max(ans, tmp);
			}
		}
	}
	printf("%.10Lf\n", ans);
	exit(0);
}
