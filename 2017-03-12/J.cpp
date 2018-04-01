#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 60001;
int n, m, ord[maxn];
struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
	bool operator < (Point const &t) const {
		return x < t.x || (x == t.x && y < t.y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	LL det(Point const &t) const {
		return (LL)x * t.y - (LL)y * t.x;
	}
} p[maxn];
bool ban[maxn];
void solve()
{
	int len = 0;
	static int stack[maxn];
	for(int i = 0; i < n + m; ++i)
		if(ord[i] < n) // add
		{
			for( ; len > 1 && (p[stack[len - 1]] - p[stack[len - 2]]).det(p[ord[i]] - p[stack[len - 2]]) <= 0; --len);
			stack[len++] = ord[i];
		}
	for(int i = 0, j = 0; i < n + m; ++i)
		if(ord[i] >= n) // query
		{
			for( ; j < len && p[stack[j]] < p[ord[i]]; ++j);
			if(j == 0 || j == len || (p[stack[j]] - p[stack[j - 1]]).det(p[ord[i]] - p[stack[j - 1]]) < 0)
				ban[ord[i]] = 1;
		}
}
bool cmp(int const &x, int const &y)
{
	return p[x] < p[y];
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		p[i].read();
		ord[i] = i;
	}
	scanf("%d", &m);
	for(int i = n; i < n + m; ++i)
	{
		p[i].read();
		ord[i] = i;
		ban[i] = 0;
	}
	sort(ord, ord + n + m, cmp);
	solve();
	for(int i = 0; i < n + m; ++i)
	{
		p[i].x = -p[i].x;
		p[i].y = -p[i].y;
	}
	reverse(ord, ord + n + m);
	solve();
	int ans = 0;
	for(int i = n; i < n + m; ++i)
		ans += !ban[i];
	printf("%d\n", ans);
	return 0;
}
