#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int n, a[maxn], b[maxn], c[maxn], ord[maxn];
long long f[maxn];
int main() {
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 1; i <= n; ++i) {
			scanf("%d%d%d", a + i, b + i, c + i);
			ord[i] = i;
			f[i] = 0;
		}
		sort(ord + 1, ord + n + 1, [&](int const &u, int const &v) {
			return a[u] + max(b[u] + c[u], a[v] + b[v]) + c[v] < a[v] + max(b[v] + c[v], a[u] + b[u]) + c[u];
		});
		for(int i = 1; i <= n; ++i)
			f[i] = max(f[i - 1], f[i]) + a[ord[i]];
		for(int i = 1; i <= n; ++i)
			f[i] = max(f[i - 1], f[i]) + b[ord[i]];
		for(int i = 1; i <= n; ++i)
			f[i] = max(f[i - 1], f[i]) + c[ord[i]];
		printf("%lld\n", f[n]);
	}
	return 0;
}
