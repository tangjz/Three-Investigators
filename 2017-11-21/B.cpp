#include <bits/stdc++.h>
using namespace std;
typedef long double DB;
const int maxn = 51;
const DB eps = 1e-10;
int t, n, m, ord[maxn];
DB dis[maxn][maxn], val[maxn];
inline int dcmp(DB x) {
	return (x > eps) - (x < -eps);
}
inline DB sqr(DB x) {
	return x * x;
}
int main() {
	static int a[maxn][3], b[maxn][maxn];
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d%d%d", a[i] + 0, a[i] + 1, a[i] + 2);
		bool chk = 1;
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j) {
				scanf("%d", b[i] + j);
				dis[i][j] = b[i][j] - sqr(a[i][0] - a[j][0]) - sqr(a[i][1] - a[j][1]) - sqr(a[i][2] - a[j][2]);
				chk &= dcmp(dis[i][j]) >= 0;
			}
		m = 0;
		for(int i = 1; chk && i < n; ++i) {
			if(!dcmp(dis[0][i]))
				continue;
			for(int j = 0; j < i; ++j)
				val[j] = 0;
			val[i] = sqrtl(dis[0][i]);
			for(int j = i + 1; j < n; ++j)
				val[j] = (dis[0][j] - dis[i][j] + dis[0][i]) / 2 / val[i];
			for(int j = 0; j < n; ++j)
				for(int k = j + 1; k < n; ++k) {
					dis[j][k] -= sqr(val[j] - val[k]);
					chk &= dcmp(dis[j][k]) >= 0;
				}
			++m;
		}
		if(chk) {
			printf("%d\n", m + 3);
		} else {
			puts("Goodbye World!");
		}
	}
	return 0;
}
