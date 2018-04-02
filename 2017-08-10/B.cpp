#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

int T, R;
long double c, d;

inline int sqr(int x)
{
	return x * x;
}

inline long double sqr(long double x)
{
	return x * x;
}

int main()
{
	int t, x1, x2, y1, y2;
	long double y0;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		scanf("%d", &R);
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		c = sqrt(sqr(x1 - x2) + sqr(y1 - y2)) / 2.0;
		d = sqrt(sqr(x1 + x2) + sqr(y1 + y2)) / 2.0;
		y0 = (d * sqr(c) * sqr(R) - sqr(d) * d * sqr(c) - sqr(sqr(c)) * d) /(sqr(c * c) + sqr(d * c));
		if(y0 <= R - d)
			printf("%.8f\n", (double)(2 * min(sqrt(sqr(c * R) / (sqr(c) + sqr(d))), min(sqrt(sqr(R) - sqr(d)), sqrt(sqr(R - d) + sqr(c))))));
		else
			printf("%.8f\n", (double)(2 * min(sqrt(sqr(R) - sqr(d)), sqrt(sqr(R - d) + sqr(c)))));

	}
	exit(0);
}
