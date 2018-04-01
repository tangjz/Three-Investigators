#include <queue>
#include <cstdio>
using namespace std;
typedef long long LL;
int t, n;
LL ans;
priority_queue<LL> Q;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		for( ; !Q.empty(); Q.pop());
		scanf("%d", &n);
		for(int i = 0, x; i < n; ++i)
		{
			scanf("%d", &x);
			Q.push(-x);
		}
		for(int i = 1; i < n; ++i)
		{
			LL val = Q.top(); Q.pop();
			val += Q.top(); Q.pop();
			ans += val; Q.push(val);
		}
		printf("%lld\n", -ans);
	}
	return 0;
}

