#include <bitset>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001;
bitset<1001> A, B;
bitset<100001> C, D;
int t, n, m, w, a[maxn], b[maxn], ord1[maxn], ord2[maxn];
void solve1() {
	auto cur = A, sum = B;
	cur.reset();
	sum.reset();
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		if(a[i] <= 1)
			--a[i];
		ord1[i] = i;
	}
	sort(ord1, ord1 + n, [&](int const &u, int const &v) {
		return a[u] < a[v];
	});
	for(int i = 0; i < m; ++i) {
		scanf("%d", b + i);
		if(b[i] <= 1)
			--b[i];
		if(b[i] >= 0)
			cur.set(i);
		ord2[i] = i;
	}
	sort(ord2, ord2 + m, [&](int const &u, int const &v) {
		return b[u] < b[v];
	});
	for(int i = n - 1, j = 0; i >= 0; --i) {
		for( ; j < m && b[ord2[j]] <= w - a[ord1[i]]; ++j)
			if(b[ord2[j]] >= 0)
				cur.reset(ord2[j]);
		if(j == m)
			break;
		if(a[ord1[i]] >= 0)
			sum |= cur << ord1[i];
	}
	for(int i = 0; i < n + m - 1; ++i)
		putchar(sum.test(i) ? 'Y' : 'N');
	putchar('\n');
}
void solve2() {
	auto cur = C, sum = D;
	cur.reset();
	sum.reset();
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		if(a[i] <= 1)
			--a[i];
		ord1[i] = i;
	}
	sort(ord1, ord1 + n, [&](int const &u, int const &v) {
		return a[u] < a[v];
	});
	for(int i = 0; i < m; ++i) {
		scanf("%d", b + i);
		if(b[i] <= 1)
			--b[i];
		if(b[i] >= 0)
			cur.set(i);
		ord2[i] = i;
	}
	sort(ord2, ord2 + m, [&](int const &u, int const &v) {
		return b[u] < b[v];
	});
	for(int i = n - 1, j = 0; i >= 0; --i) {
		for( ; j < m && b[ord2[j]] <= w - a[ord1[i]]; ++j)
			if(b[ord2[j]] >= 0)
				cur.reset(ord2[j]);
		if(j == m)
			break;
		if(a[ord1[i]] >= 0)
			sum |= cur << ord1[i];
	}
	for(int i = 0; i < n + m - 1; ++i)
		putchar(sum.test(i) ? 'Y' : 'N');
	putchar('\n');
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &m, &w);
		if(n + m <= 1000)
			solve1();
		else
			solve2();
	}
	return 0;
}
