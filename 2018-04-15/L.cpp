#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int n, m, cur, pre = 1, ord[maxn];
LL S, T, a[maxn], f[2][2][maxn];
int main() {
	scanf("%d%d%lld%lld", &n, &m, &S, &T);
	LL msk = 0;
	for(int i = 0; i < n; ++i) {
		scanf("%lld", a + i);
		msk ^= a[i];
		ord[i] = i;
	}
	f[cur][0][0] = f[cur][1][0] = 1;
	for(int i = 0; i < m; ++i) {
		swap(cur, pre);
		memset(f[cur][0], 0, (n + 1) * sizeof(LL));
		memset(f[cur][1], 0, (n + 1) * sizeof(LL));
		int tot = 0, odd = 0;
		bool good = (S >> i) & 1;
		static int tmp[maxn];
		for(int j = 0; j < n; ++j)
			odd += (a[j] >> i) & 1;
		for(int j = 0; j <= n; ++j) {
			if(((odd + j - tot - tot) & 1) == good) {
				f[cur][0][tot] += f[pre][0][j];
				if(!((T >> i) & 1)) {
					f[cur][1][tot] += f[pre][1][j];
				} else {
					f[cur][1][tot] += f[pre][0][j];
				}
			}
			if(((n - odd - j + tot + tot) & 1) == good) {
				f[cur][0][odd + j - tot] += f[pre][0][j];
				if((T >> i) & 1)
					f[cur][1][odd + j - tot] += f[pre][1][j];
			}
			if(j < n && (a[ord[j]] >> i) & 1)
					tmp[tot++] = ord[j];
		}
		for(int j = 0; j < n; ++j)
			if(!((a[ord[j]] >> i) & 1))
				tmp[tot++] = ord[j];
		memcpy(ord, tmp, n * sizeof(int));
	}
	LL ans[2] = {};
	for(int i = 0; i <= n; ++i) {
		ans[0] += f[cur][0][i];
		ans[1] += f[cur][1][i];
	}
	printf("%lld\n", ans[0] * (T >> m) + ans[1] - (msk == S));
	return 0;
}