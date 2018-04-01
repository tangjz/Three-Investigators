#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 21000;
const double eps = 1e-8;

struct Point
{
	double x;
	double y;
	int type;
	operator<(const Point &v)
	const{
		if(fabs(x - v.x) < eps)
			return y < v.y - eps;
		return x < v.x - eps;
	}
};

struct Segment
{
	Point l;
	Point r;

	void getLine(double &k, double &b)
	const{
		k = (r.y - l.y) / (r.x - l.x);
		b = -k * l.x + l.y;
	}

	double yAt(const double &x)
	const{
		return (r.y - l.y) / (r.x - l.x) * (x - l.x) + l.y;
	}
};

struct Parabola
{
	double a;
	double b;
	double c;

	double yAt(const double &x)
	const{
		return a * x * x + b * x + c;
	}

	double deriveAt(const double &x)
	const{
		return 2 * a * x + b;
	}

	int side(const Point &u, const Point &v)
	const{
		double delta = (v.y - u.y) - deriveAt(u.x) * (v.x - u.x);
		if(fabs(delta) < eps)
			return a > 0?-1:1;
		return delta < 0?-1:1;
	}

	double delta()
	const{
		return b * b - 4 * a * c;
	}

	double symAxis()
	const{
		return -b / a;
	}
};

int N, L, R;
double ans;
Parabola para;
Point poly[NMAX];
Segment polyLine[NMAX];
vector<Point> intern;

inline bool inInterval(double l, double x, double r)
{
	return l + eps < x && x < r - eps;
}

void internSegPara(const Segment &u, const Parabola &p)
{
	double x, y;
	//printf("solve (%f, %f)->(%f, %f) intersection\n", u.l.x, u.l.y, u.r.x, u.r.y);
	if(fabs(u.l.x - u.r.x) < eps)
	{
		//printf("same x\n");
		x = u.l.x;
		y = p.yAt(x);
		if(inInterval(u.l.y, y, u.r.y))
			intern.push_back((Point){x, y});
	}
	else
	{
		double k, b, base, delta;
		Parabola equ;
		u.getLine(k, b);
		//printf("k:%f, b:%f\n", k, b);
		equ = (Parabola){p.a, p.b - k, p.c - b};
		delta = equ.delta();
		base = equ.symAxis() / 2.0;
		if(fabs(delta) > eps)
		{
			delta = sqrt(delta) / 2.0 / para.a;
			//printf("delta > 0: %f %f\n", delta);
			y = u.yAt(x = base + delta);
			if(inInterval(u.l.x, x, u.r.x))
				intern.push_back((Point){x, y, 1});
			y = u.yAt(x = base - delta);
			if(inInterval(u.l.x, x, u.r.x))
				intern.push_back((Point){x, y, 1});
		}
		/*
		else
			printf("delta <= 0\n");
		*/
	}
}


double sqr(double x)
{
	return x * x;
}

inline double f(const double &x)
{
	double a = para.a, b = para.b;
	double delta = 2 * a * x + b, tmp = sqrt(sqr(delta) + 1);
	return b * tmp / 4 / a + 0.5 * x * tmp + log(tmp + delta) / 4 / a;
}

double len(double l, double r)
{
	return f(r) - f(l);
}

int main()
{
	int i, a, b, c, x, y;
	int indicate;
	while(scanf("%d %d %d %d %d %d", &N, &a, &b, &c, &L, &R) != EOF)
	{
		ans = 0.0;
		indicate = 0;
		intern.erase(intern.begin(), intern.end());
		para = (Parabola){(double)a, (double)b, (double)c};
		for(i = 0;i < N;i += 1)
		{
			scanf("%d %d", &x, &y);
			poly[i] = (Point){(double)x, (double)y, 1};
		}
		intern.push_back((Point){(double)L, para.yAt(L), 0});
		intern.push_back((Point){(double)R, para.yAt(R), 0});
		for(i = 0;i < N;i += 1)
		{
			if(poly[i] < poly[(i + 1) % N])
				polyLine[i] = (Segment){poly[i], poly[(i + 1) % N]};
			else
				polyLine[i] = (Segment){poly[(i + 1) % N], poly[i]};
			internSegPara(polyLine[i], para);
			if(fabs(para.yAt(poly[i].x) - poly[i].y) < eps && para.side(poly[i], poly[(i - 1 + N) % N]) * para.side(poly[i], poly[(i + 1) % N]) < 0)
				intern.push_back(poly[i]);
		}
		sort(intern.begin(), intern.end());
		/*
		for(i = 0;i < intern.size();i += 1)
			printf("(%f, %f): %d\n", intern[i].x, intern[i].y, intern[i].type);
		*/
		for(i = 0;i + 1 < intern.size();i += 1)
		{
			indicate ^= intern[i].type;
			if(indicate && L - eps < intern[i].x && intern[i + 1].x < R + eps)
				ans += len(intern[i].x, intern[i + 1].x);
		}
		printf("%.2f\n", ans);
	}
	exit(0);
}
