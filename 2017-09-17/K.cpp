#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int T;
long long P;

int main()
{
	int t;
	long long n;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		scanf("%I64d", &P);
		n = sqrt((P - 1) / (long double)3.0);
		if(3 * n * (n + 1) + 1 == P)
			printf("YES\n");
		else
			printf("NO\n");
	}
	exit(0);
}
