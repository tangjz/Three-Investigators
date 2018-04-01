#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int PMAX = 10000010, NMAX = 10000010;

int T, N;
int prime[PMAX], cnt[NMAX];
bool notPrime[NMAX];
int sum[NMAX];

void genPrime()
{
	int i, j, x;
	for(i = 2;i < NMAX;i += 1)
	{
		cnt[i] = cnt[i - 1];
		sum[i] += sum[i - 1];
		if(!notPrime[i])
		{
			prime[++prime[0]] = i;
			cnt[i] += 1;
			sum[i] += (int)sqrt(i) - 1;
		}
		for(j = 1;j <= prime[0] && (x = i * prime[j]) < NMAX;j += 1)
		{
			notPrime[x] = true;
			sum[x] += prime[j] - 1;
			if(!(i % prime[j]))
				break;
		}
	}
}

int main()
{
	int t;
	int x, y, d;
	genPrime();
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		scanf("%d", &N);
		x = sum[N];
		y = cnt[N];
		d = __gcd(x, y);
		printf("%d/%d\n", x / d, y / d);
	}
	exit(0);
}
