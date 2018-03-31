#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int N, K;
long long ans;
vector<pair<int, int> > pos, neg;

void solve(vector<pair<int, int> > &Q)
{
	int x, m, left, delta;
	while(!Q.empty())
	{
		x = Q.back().first;
		m = Q.back().second;
		Q.pop_back();
		ans += (long long)2 * x * ((m + K - 1) / K);
		left = ((m + K - 1) / K) * K - m;
		while(left && !Q.empty())
		{
			delta = min(left, Q.back().second);
			left -= delta;
			Q[Q.size() - 1].second -= delta;
			if(!Q[Q.size() - 1].second)
				Q.pop_back();
			else
				break;
		}
	}
}

int main()
{
	int i, x, m;
	scanf("%d %d", &N, &K);
	for(i = 0;i < N;i += 1)
	{
		scanf("%d %d", &x, &m);
		if(x < 0)
			neg.push_back(make_pair(-x, m));
		else if(x > 0)
			pos.push_back(make_pair(x, m));
	}
	sort(pos.begin(), pos.end());
	sort(neg.begin(), neg.end());
	solve(pos);
	solve(neg);
	printf("%I64d\n", ans);
	exit(0);
}
