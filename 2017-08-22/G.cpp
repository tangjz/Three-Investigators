#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int NMAX = 110;
const double eps = 1e-8;

struct Missile
{
	int x;
	int y;
	int dx;
	int dy;
	int v;
};

struct Circle
{
	double x;
	double y;
	double r;
};

int N, V;
Circle cir[NMAX];

inline double sqr(const double x)
{
	return x * x;
}

int check2(double x)
{
	int i;
	int posB, posH;
	double delta, b, h, dist2;
	double bMax = -500000, hMin = 500000;
	for(i = 1;i <= N;i += 1)
	{
		delta = sqrt(sqr(cir[i].r) - sqr(cir[i].x - x));
		b = cir[i].y - delta;
		h = cir[i].y + delta;
		if(b > bMax + eps)
		{
			bMax = b;
			posB = i;
		}
		if(h + eps < hMin)
		{
			hMin = h;
			posH = i;
		}
	}
	if(hMin - bMax >= eps)
		return 0;
	if((dist2 = sqr(cir[posH].x - cir[posB].x) + sqr(cir[posH].y - cir[posB].y)) - sqr(cir[posH].r + cir[posB].r) > -eps)
		return -1;
	return ((sqr(cir[posB].r) + dist2 - sqr(cir[posH].r)) * cir[posH].x + (sqr(cir[posH].r) + dist2 - sqr(cir[posB].r)) * cir[posB].x) / (2 * dist2) + eps > x?1:2;
}

Missile miss[NMAX];

bool check(double t)
{
	int i, res;
	double l = -500000, r = 500000, mid;
	for(i = 1;i <= N;i += 1)
	{
		cir[i].x = miss[i].x + miss[i].dx * miss[i].v * t / sqrt(sqr(miss[i].dx) + sqr(miss[i].dy));
		cir[i].y = miss[i].y + miss[i].dy * miss[i].v * t / sqrt(sqr(miss[i].dx) + sqr(miss[i].dy));
		cir[i].r = V * t;
	}
	for(i = 1;i <= N;i += 1)
	{
		l = max(l, cir[i].x - cir[i].r);
		r = min(r, cir[i].x + cir[i].r);
	}
	if(l - r > eps)
		return false;
	for(i = 1;i <= 30;i += 1)
	{
		mid = (l + r) / 2;
		res = check2(mid);
		if(!res)
			return true;
		if(res < 0)
			return false;
		if(res == 1)
			l = mid;
		else
			r = mid;
	}
	return false;
}

int main()
{
	int i;
	double l, r, mid;
	while(scanf("%d %d", &N, &V) != EOF)
	{
		for(i = 1;i <= N;i += 1)
			scanf("%d %d %d %d %d", &miss[i].x, &miss[i].y, &miss[i].dx, &miss[i].dy, &miss[i].v);
		l = 0.0;
		r = 2100.0;
		for(i = 1;i <= 35;i += 1)
		{
			mid = (l + r) / 2;
			if(check(mid))
				r = mid;
			else
				l = mid;
		}
		printf("%.4f\n", r);
	}
}
