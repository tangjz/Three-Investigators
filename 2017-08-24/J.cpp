#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int T;
int N, need;
long long ans;
vector<pair<int, int> > miss;
priority_queue<pair<int, int> > blank;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > busy;

int main()
{
	int t, i, l, r;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		ans = need = 0;
		while(!blank.empty())
			blank.pop();
		while(!busy.empty())
			busy.pop();
		miss.clear();
		scanf("%d", &N);
		for(i = 1;i <= N;i += 1)
		{
			scanf("%d %d", &l, &r);
			miss.push_back(make_pair(l, r));
		}
		sort(miss.begin(), miss.end());
		for(i = 0;i < N;i += 1)
		{
			while(!busy.empty() && busy.top().first <= miss[i].first)
			{
				blank.push(busy.top());
				busy.pop();
			}
			if(blank.empty())
				busy.push(make_pair(miss[i].second, ++need));
			else
			{
				busy.push(make_pair(miss[i].second, blank.top().second));
				ans += miss[i].first - blank.top().first;
				blank.pop();
			}
			ans += miss[i].second - miss[i].first;
		}
		printf("%d %lld\n", need, ans);
	}
	exit(0);
}
