#include <bits/stdc++.h>
using namespace std;
typedef long double DB;
const int maxn = 5001, maxt = 101;
int n, a[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	DB L = 0, R = 2e3;
	for(int i = 0; i < maxt; ++i) {
		DB M = L + (R - L) * 0.5, sum = 0;
		for(int j = 0; j < n; ++j)
			sum += max(1 - pow(M / a[j], 1.0 / (n - 1)), (DB)0);
		if(sum > 1)
			L = M;
		else
			R = M;
	}
	DB ans = 0;
	for(int i = 0; i < n; ++i)
		ans += a[i] * (1 - pow(min(pow(L / a[i], 1.0 / (n - 1)), (DB)1), n));
	printf("%.20f\n", (double)(ans / n));
	return 0;
}
