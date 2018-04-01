#include <bits/stdc++.h>
using namespace std;
const int maxn = 1 << 20 | 1;
int n, m, a[maxn];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < 1 << n; ++i)
		scanf("%d", a + i);
	if(m & 1)
		reverse(a, a + (1 << n));
	for(int i = 0; i < 1 << n; ++i)
		printf("%d%c", a[i], " \n"[i == (1 << n) - 1]);
	return 0;
}