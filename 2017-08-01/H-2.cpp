#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

long long N, K;

int quickModPow(int x, int y)
{
	int res = 1;
	while(y)
	{
		if(y & 1)
			res = (long long)res * x % MOD;
		x = (long long)x * x % MOD;
		y >>= 1;
	}
	return res;
}

int main()
{
	int t;
	for(t = 1;scanf("%lld %lld", &N, &K) != EOF;t += 1)
		printf("Case #%d: %d\n", t, quickModPow(N % MOD, K % (MOD - 1)));
	exit(0);
}
