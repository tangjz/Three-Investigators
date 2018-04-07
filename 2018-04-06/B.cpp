#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int CMAX = 50;
const long double PI = acos(-1.0);

int N, I;
double A[CMAX], B[CMAX];
double L, H;

double f(double x)
{
	int i;
	double res = 0.0;
	for(i = 2 * N + 1;i >= 0;i -= 1)
		res = res * x + B[i];
	return res * PI;
}

int main()
{
	int t = 0;
	int i, j;
	double total, cur;
	double l, h, mid;
	while(scanf("%d", &N) != EOF)
	{
		t += 1;
		memset(B, 0, sizeof(B));
		for(i = 0;i <= N;i += 1)
			scanf("%lf", &A[i]);
		for(i = 0;i <= N;i += 1)
		{
			for(j = 0;j <= N;j += 1)
				B[i + j] += A[i] * A[j];
		}
		for(i = 2 * N + 1;i;i -= 1)
			B[i] = B[i - 1] / i;
		B[0] = 0;
		scanf("%lf %lf", &L, &H);
		scanf("%d", &I);
		printf("Case %d: %.2f\n", t, total = f(H) - f(L));
		if(total < I)
			printf("insufficient volume\n");
		else
		{
			for(i = 1, cur = L;i <= 8 && i * I <= total;i += 1)
			{
				l = cur;
				h = H;
				for(j = 0;j < 64;j += 1)
				{
					mid = (l + h) / 2;
					if(f(mid) - f(cur) >= I)
						h = mid;
					else
						l = mid;
				}
				if(i > 1)
					printf(" ");
				printf("%.2f", l - L);
				cur = l;
			}
			printf("\n");
		}
	}
	exit(0);
}
