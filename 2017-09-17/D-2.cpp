#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int T, K;

struct Fraction
{
	long long x;
	long long y;
	Fraction(long long __x = 0, long long __y = 1)
	{
		x = __x;
		y = __y;
	}
};

int main()
{
	int t;
	long long d;
	Fraction l, r, mid, ans;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		scanf("%d", &K);
		l = Fraction(max(0, (int)pow((long long)K * K, 1/3.0) - 1), 1);
		r = Fraction(1, 0);
		while(1)
		{
			mid = Fraction(l.x + r.x, l.y + r.y);
			if(mid.y > 100000)
				break;
			if((__int128)mid.x * mid.x * mid.x < (__int128)mid.y * mid.y * mid.y * K * K)
				l = mid;
			else
				r = mid;
		}
		mid = Fraction(l.x * r.y + r.x * l.y, 2 * l.y * r.y);
		d = __gcd(mid.x, mid.y);
		mid = Fraction(mid.x / d, mid.y / d);
		if((__int128)mid.x * mid.x * mid.x < (__int128)mid.y * mid.y * mid.y * K * K)
			ans = r;
		else
			ans = l;
		printf("%lld/%lld\n", ans.x, ans.y);
	}
	exit(0);
}
