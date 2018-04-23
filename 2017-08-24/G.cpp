#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const long double eps = 1e-6;

int T;
long long N, M, A, B;

long double prox(long double last, int k, long double ln, long double lln)
{
	long double r = last * ln;
	if(k - 2 >= 0)
		r += lln;
	return r;
}

int check(long long n, long long a, long long m, long long b)
{
	int i;
	long double x = 1, y = 1, r, ln, lm;
	long double lln, llm;
	if(n == m)
	{
		if(n != 1)
		{
			if(a == b)
				return 0;
			if(a < b)
				return -1;
			if(a > b)
				return 1;
		}
		else
			return 0;
	}
	if(n == 1 || a <= b)
		return -1;
	ln = log(n) / log(2);
	lm = log(m) / log(2);
	lln = log(ln) / log(2);
	llm = log(lm) / log(2);
	printf("ln:%Lf lm:%Lf\n", ln, lm);
	for(i = 0;i < a - b;i += 1)
	{
		printf("px:%Lf, py:%Lf\n", prox(x, a - i, ln, lln), prox(0, a - i, lm, llm));
		if(prox(x, a - i, ln, lln) - prox(0, a - i, lm, llm) >= 1)
			return 1;
		x = pow(n, x);
	}
	printf("px:%Lf, py:%Lf\n", prox(x, b, ln, lln), prox(1, b, lm, llm));
	if((r = prox(x, b, ln, lln) - prox(1, b, lm, llm)) >= 0.3)
		return 1;
	if(r < -0.3)
		return -1;
	for(i = 1;i < b;i += 1)
	{
		x = pow(n, x);
		y = pow(m, y);
		printf("x:%Lf y:%Lf\n", x, y);
		printf("px:%Lf, py:%Lf\n", prox(x, b - i, ln, lln), prox(y, b - i, lm, llm));
		if((r = prox(x, b - i, ln, lln) - prox(y, b - i, lm, llm)) >= 0.3)
			return 1;
		if(r <= -0.3)
			return -1;
	}
	r = pow(n, x) - pow(m, y);
	if(fabs(r) < eps)
		return 0;
	return r > 0?1:-1;
}

void output(int r)
{
	if(r > 0)
		printf(">\n");
	else if(!r)
		printf("=\n");
	else
		printf("<\n");
}

int main()
{
	int delta = 3;
	long long l, r, mid;
	for(N = 2;N <= 2;N += 1)
	{
		A = 6;
		l = N + 1;
		r = 4500000000000000000LL;
		while(l + 1 < r)
		{
			printf("------------\n");
			mid = (l + r)>>1;
			if(check(N, A, mid, A - delta) > 0)
				l = mid;
			else
				r = mid;
		}
		printf("%lld %lld\n", l, r);
		check(N, A, l, A - delta);
		check(N, A, r, A - delta);
	}
	/*
	int t;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		scanf("%lld %lld %lld %lld", &N, &A, &M, &B);
		if(N > M)
			output(-check(M, B, N, A));
		else
			output(check(N, A, M, B));
	}
	*/
	exit(0);
}
