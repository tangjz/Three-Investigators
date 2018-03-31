#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long double DB;
const int maxn = 100, maxc = 6;
int t, m, nxt[maxn + 1];
DB mat[maxn][maxn + 1];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &m);
		memset(nxt, -1, sizeof nxt);
		while(m--) {
			int x, y;
			scanf("%d%d", &x, &y);
			nxt[--x] = --y;
		}
		for(int i = 0; i < maxn; ++i) {
			for(int j = 0; j <= maxn; ++j)
				mat[i][j] = 0;
			if(nxt[i] != -1) {
				mat[i][i] = 1;
				mat[i][nxt[i]] = -1;
			} else if(i + 1 < maxn) {
				int c = std::min(maxn - i - 1, maxc);
				mat[i][i] = c;
				for(int j = i + 1; j <= i + c; ++j)
					mat[i][j] = -1;
				mat[i][maxn] = maxc;
			} else {
				mat[i][i] = 1;
			}
		}
		for(int i = 0; i < maxn; ++i) {
			int k = i;
			for(int j = k + 1; j < maxn; ++j)
				if(fabs(mat[k][i]) < fabs(mat[j][i]))
					k = j;
			for(int j = maxn; j >= i; --j) {
				mat[k][j] /= mat[k][i];
				std::swap(mat[i][j], mat[k][j]);
			}
			for(int j = 0; j < maxn; ++j) {
				if(j == i)
					continue;
				for(int k = maxn; k >= i; --k)
					mat[j][k] -= mat[j][i] * mat[i][k];
			}
		}
		printf("Case %d: %.10f\n", Case, (double)mat[0][maxn]);
	}
	return 0;
}
