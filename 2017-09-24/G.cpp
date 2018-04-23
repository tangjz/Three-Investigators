#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int T;
double R;
double y[20], r[20];

double sqr(double x)
{
	return x * x;
}

int main()
{
	int t, k;
	int i;
	double xx, yy;
	scanf("%d", &T);
	scanf("%lf", &R);
	y[1] = 0;
	r[1] = (2 * sqrt(3.0) - 3) / 3 * R;
	xx = R;
	yy = R / sqrt(3.0);
	for(i = 2;i <= 10;i += 1)
	{
		y[i] = (sqr(xx) + sqr(yy) - sqr(R - y[i - 1] - r[i - 1])) / 2.0 / (R - y[i - 1] - r[i - 1] + yy);
		r[i] = y[i] - y[i - 1] - r[i - 1];
	}
	for(t = 0;t < T;t += 1)
	{
		scanf("%d", &k);
		printf("%d %d\n", k, (int)r[k]);
	}
	exit(0);
}
