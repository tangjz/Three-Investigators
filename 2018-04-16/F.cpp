#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1;
int n, m, q;
LL solve(int A, int B, int C, int K) { // A x - B y + C >= 0 (0 <= x <= K)
	LL ret = 0;
	while(1) {
		int rA = A / B, rC = C / B;
		ret += K * (K + 1LL) / 2 * rA + (K + 1LL) * rC;
		A -= B * rA;
		C -= B * rC;
		if(!A) {
			ret += K + 1LL;
			return ret;
		}
		int KK = ((LL)A * K + C) / B, CC = ((LL)A * K + C) % B;
		ret -= max(max(((LL)B * KK + CC) / A, 0LL) - K, 0LL);
		swap(A, B);
		K = KK;
		C = CC;
	}
}
int main() {
	while(scanf("%d%d%d", &n, &m, &q) == 3)
		while(q--) {
			LL ctr;
			scanf("%lld", &ctr);
			if(ctr < m) {
				printf("%d %d\n", 1, (int)(ctr + 1));
				continue;
			}
			if((LL)n * m - ctr < n) {
				printf("%d %d\n", n - (int)((LL)n * m - 1 - ctr), 1);
				continue;
			}
			int AL = 0, BL = 1, AR = 1, BR = 0; // y/x <= A/B
			while(1) { // [cnt - all, cnt - 1]
				int AM = AL + AR, BM = BL + BR;
				if(AM >= n || BM >= m)
					break;
				int lim = min(((LL)BM * n - 1) / AM, m - 1LL), all = min((n - 1) / AM, (m - 1) / BM);
				LL cnt = solve(AM, BM, 0, lim) + (LL)max(m - 1 - lim, 0) * n;
				if(ctr >= cnt) {
					AL = AM;
					BL = BM;
				} else if(ctr < cnt - all) {
					AR = AM;
					BR = BM;
				} else {
					int rate = all - cnt + 1 + ctr;
					printf("%d %d\n", AM * rate + 1, BM * rate + 1);
					break;
				}
			}
		}
	return 0;
}
