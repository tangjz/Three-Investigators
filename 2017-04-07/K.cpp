#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int NMAX = 1050000, P2MAX = 21;

int N, K, R;
double ans, preFacLog[NMAX];

int main()
{
	int i;
	for(i = 1;i < NMAX;i += 1)
		preFacLog[i] = preFacLog[i - 1] + log(i);
	scanf("%d %d", &K, &R);
	N = 1<<K;
	R = N - R + 1;
	for(i = 2;i - 1 <= R - 1;i *= 2)
		ans += exp(log(N / i) + preFacLog[R - 1] - preFacLog[i - 1] - preFacLog[R - i] + preFacLog[i] + preFacLog[N - i] - preFacLog[N]);
	printf("%.5f\n", ans);
	exit(0);
}
