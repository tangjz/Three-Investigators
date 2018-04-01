#include <cstdio>
typedef long long LL;
typedef __int128_t int128;
const int maxn = 100001;
int fz[maxn], fm[maxn];
inline LL sqr(int x) {
	return (LL)x * x;
}
inline __int128_t cub(LL x) {
	return (__int128_t)x * x * x;
}
int main() {
	for(int k = 1; k < maxn; ++k) {
		int xL = 0, yL = 1, xM, yM, xR = 1, yR = 0;
		while(1) {
			xM = xL + xR;
			yM = yL + yR;
			if(yM >= maxn)
				break;
			bool flag = cub(xM) < sqr(k) * cub(yM);
			(flag ? xL : xR) = xM;
			(flag ? yL : yR) = yM;
		}
		bool flag = cub((LL)xR * yL + (LL)xL * yR) >= 8 * sqr(k) * cub((LL)yL * yR);
		fz[k] = flag ? xL : xR;
		fm[k] = flag ? yL : yR;
	}
	int t, k;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &k);
		printf("%d/%d\n", fz[k], fm[k]);
	}
	return 0;
}
