#include <bits/stdc++.h>
using namespace std;
const int maxn = 11, maxv = (int)2e4 + 1, maxm = (int)1e6 + 1;
int n, m, a[maxn], mx, p[maxv], que[maxv], L, R, tot, out[maxm][3];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		if(a[mx] < a[i])
			mx = i;
	}
	memset(p, 0, sizeof p);
	que[R++] = 0;
	while(L < R) {
		int u = que[L++];
		for(int i = 1; i <= n; ++i) {
			int v = u + a[i];
			if(v <= a[mx] && !p[v]) {
				p[v] = i;
				que[R++] = v;
			}
			v = u - a[i];
			if(v > 0 && !p[v]) {
				p[v] = -i;
				que[R++] = v;
			}
			v = u + a[mx] - a[i];
			if(u < a[i] && v <= a[mx] && !p[v]) {
				p[v] = n + i;
				que[R++] = v;
			}
		}
	}
	if(!p[m]) {
		puts("-1");
	} else {
		while(m)
			if(p[m] < 0) {
				out[tot][0] = 2;
				out[tot][1] = -p[m];
				++tot;
				out[tot][0] = 3;
				out[tot][1] = mx;
				out[tot][2] = -p[m];
				++tot;
				m += a[-p[m]];
			} else if(p[m] <= n) {
				if(p[m] != mx) {
					out[tot][0] = 3;
					out[tot][1] = p[m];
					out[tot][2] = mx;
					++tot;
				}
				out[tot][0] = 1;
				out[tot][1] = p[m];
				++tot;
				m -= a[p[m]];
			} else {
				out[tot][0] = 2;
				out[tot][1] = p[m] - n;
				++tot;
				out[tot][0] = 3;
				out[tot][1] = mx;
				out[tot][2] = p[m] - n;
				++tot;
				out[tot][0] = 1;
				out[tot][1] = mx;
				++tot;
				out[tot][0] = 3;
				out[tot][1] = mx;
				out[tot][2] = p[m] - n;
				++tot;
				m -= a[mx] - a[p[m] - n];
			}
		printf("%d\n", tot);
		for(int i = tot - 1; i >= 0; --i)
			if(out[i][0] < 3)
				printf("%d %d\n", out[i][0], out[i][1]);
			else
				printf("%d %d %d\n", out[i][0], out[i][1], out[i][2]);
	}
	return 0;
}
