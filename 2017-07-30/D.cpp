#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 210000;
const double eps = 1e-6;

int T;
int N, L, D;
int X[NMAX], Y[NMAX];
double prefArea[NMAX], maxArea, base;

double calcLeftArea(int right, int length)
{
	if(!length)
		return 0;
	double leftY = Y[right] - (double)(Y[right] - Y[right - 1]) / (X[right] - X[right - 1]) * length;
	return (Y[right] + leftY) * length / 2;
}

double calcRightArea(int left, int length)
{
	if(!length)
		return 0;
	double rightY = Y[left] + (double)(Y[left] - Y[left + 1]) / (X[left] - X[left + 1]) * length;
	return (Y[left] + rightY) * length / 2;
}

int main()
{
	int t;
	int i, l, r;
	double k, b, k1, k2, b1, b2, shift;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		maxArea = 0;
		scanf("%d %d", &N, &L);
		for(i = 1;i <= N;i += 1)
			scanf("%d %d", &X[i], &Y[i]);
		for(i = 2;i <= N;i += 1)
			prefArea[i] = prefArea[i - 1] + (double)(Y[i] + Y[i - 1]) / 2.0 * (X[i] - X[i - 1]);
		scanf("%d", &D);
		for(l = 1, i = 2;i <= N;i += 1)
		{
			while(X[i] - X[l] > 2 * D)
				l += 1;
			if(X[i] >= 2 * D)
			{
				maxArea = max(maxArea, base = prefArea[i] - prefArea[l] + calcLeftArea(l, 2 * D - (X[i] - X[l])));
				if(i + 1 <= N && l > 1)
				{
					//printf("[%d [%d]] shift to right\n", X[l], X[i]);
					k1 = (double)(Y[i] - Y[i + 1]) / (X[i] - X[i + 1]);
					b1 = Y[i];
					k2 = (double)(Y[l] - Y[l - 1]) / (X[l] - X[l - 1]);
					b2 = -k2 * (2 * D - (X[i] - X[l])) + Y[l];
					k = k1 - k2;
					b = b1 - b2;
					//printf("k:%f, b:%f\n", k, b);
					if(fabs(k) > eps)
					{
						shift = -b / k;
						if(0 <= shift && shift <= min(X[i + 1] - X[i], 2 * D - (X[i] - X[l])))
							maxArea = max(maxArea, base + (k * shift + 2 * b) * shift / 2);
					}
				}
			}
		}
		for(r = N, i = N - 1;i;i -= 1)
		{
			while(X[r] - X[i] > 2 * D)
				r -= 1;
			if(X[i] + 2 * D <= L)
			{
				maxArea = max(maxArea, base = prefArea[r] - prefArea[i] + calcRightArea(r, 2 * D - (X[r] - X[i])));
				if(r + 1 <= N)
				{
					//printf("[[%d] %d] shift to right\n", X[i], X[r]);
					k1 = (double)(Y[i] - Y[i + 1]) / (X[i] - X[i + 1]);
					b1 = Y[i];
					k2 = (double)(Y[r] - Y[r + 1]) / (X[r] - X[r + 1]);
					b2 = k2 * (2 * D - (X[r] - X[i])) + Y[r];
					k = k2 - k1;
					b = b2 - b1;
					//printf("k:%f, b:%f\n", k, b);
					if(fabs(k) > eps)
					{
						shift = -b / k;
						if(0 <= shift && shift <= min(X[i + 1] - X[i], X[r + 1] - X[i] - 2 * D))
							maxArea = max(maxArea, base + (k * shift + 2 * b) * shift / 2);
					}
				}
			}
		}
		printf("%.3f\n", fabs(D) < eps?0.0:maxArea / (2 * D));
	}
	exit(0);
}
