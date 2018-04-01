#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int NMAX = 15;
const long double eps = 1e-12;

int N, L;
int len[NMAX], suf[NMAX];
long double lambda1, lambda2;

int main()
{
	int i, j, k;
	long double l, r, mid, ans, t, s, c;
	long double x, y;
	scanf("%d %d", &N, &L);
	for(i = 1;i <= N;i += 1)
		scanf("%d", &len[i]);
	for(i = N - 1;i;i -= 1)
		suf[i] = suf[i + 1] + len[i + 1];
	lambda2 = -len[1] / 2.0 - suf[1];
	for(i = 1;i < 500;i += 1)
	{
		l = -50000;
		r = 0;
		for(j = 1;j < 500;j += 1)
		{
			mid = (l + r) / 2.0;
			ans = 0.0;
			for(k = 1;k <= N;k += 1)
			{
				t = 1 / mid * (len[k] / 2.0 + suf[k] + lambda2);
				c = sqrt(1 / (1 + t * t));
				ans += len[k] * c;
			}
			if(ans < L - eps)
				r = mid;
			else
				l = mid;
		}
		lambda1 = l;
		l = -len[1] / 2.0 - suf[1];
		r = 0;
		for(j = 1;j < 500;j += 1)
		{
			mid = (l + r) / 2.0;
			ans = 0.0;
			for(k = 1;k <= N;k += 1)
			{
				t = 1 / lambda1 * (len[k] / 2.0 + suf[k] + mid);
				s = sqrt(1 / (1 + t * t)) * t;
				ans += len[k] * s;
			}
			if(ans < -eps)
				r = mid;
			else
				l = mid;
		}
		lambda2 = l;
	}
	for(i = 1, x = y = 0.0;i < N;i += 1)
	{
		t = 1 / lambda1 * (len[i] / 2.0 + suf[i] + lambda2);
		s = sqrt(1 / (1 + t * t)) * t;
		c = sqrt(1 / (1 + t * t));
		x += len[i] * c;
		y += len[i] * s;
		printf("%.10f %.10f\n", (double)x, (double)-y);
	}
	exit(0);
}

