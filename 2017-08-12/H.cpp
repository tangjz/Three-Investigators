#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int NMAX = 1100;
const double eps = 1e-6;

struct Circle
{
	int x;
	int y;
	double r;
};

int N, D;
Circle house[NMAX];

inline double sqr(const double x)
{
	return x * x;
}

int check2(int begin, int end, double x)
{
	int i;
	int posB, posH;
	double delta, b, h, dist2;
	double bMax = -500000, hMin = 500000;
	for(i = begin;i <= end;i += 1)
	{
		delta = sqrt(sqr(house[i].r) - sqr(house[i].x - x));
		b = house[i].y - delta;
		h = house[i].y + delta;
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
	if((dist2 = sqr(house[posH].x - house[posB].x) + sqr(house[posH].y - house[posB].y)) - sqr(house[posH].r + house[posB].r) > -eps)
		return -1;
	return ((sqr(house[posB].r) + dist2 - sqr(house[posH].r)) * house[posH].x + (sqr(house[posH].r) + dist2 - sqr(house[posB].r)) * house[posB].x) / (2 * dist2) + eps > x?1:2;
}

bool check(int begin, int end)
{
	int i, res;
	double l = -500000, r = 500000, mid;
	for(i = begin;i <= end;i += 1)
	{
		l = max(l, house[i].x - house[i].r);
		r = min(r, house[i].x + house[i].r);
	}
	if(l - r > eps)
		return false;
	for(i = 1;i <= 30;i += 1)
	{
		mid = (l + r) / 2;
		res = check2(begin, end, mid);
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
	while(scanf("%d %d %d", &house[0].x, &house[0].y, &D) != EOF)
	{
		scanf("%d", &N);
		for(i = 1;i <= N;i += 1)
		{
			scanf("%d %d", &house[i].x, &house[i].y);
			house[i].r = D;
		}
		if(!check(1, N))
			printf("X\n");
		else
		{
			l = 0.0;
			r = 500000.0;
			for(i = 1;i <= 35;i += 1)//(]
			{
				mid = (l + r) / 2;
				house[0].r = mid;
				if(check(0, N))
					r = mid;
				else
					l = mid;
			}
			printf("%.2f\n", r);
		}
	}
	exit(0);
}
