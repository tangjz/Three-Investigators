#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

long long X, Y;
vector<long long> ans;

int main()
{
	int i, j, k;
	long long tmp;
	for(i = 1;i <= 63;i += 1)
	{
		for(j = 1;j <= 63;j += 1)
		{
			for(k = 1, tmp = 0;(i + j) * k - j <= 63;k += 1)
			{
				tmp <<= i;
				tmp |= (1ll<<i) - 1;
				ans.push_back(tmp);
				tmp <<= j;
				if((i + j) * k <= 63)
					ans.push_back(tmp);
			}
		}
	}
	sort(ans.begin(), ans.end());
	ans.erase(unique(ans.begin(), ans.end()), ans.end());
	scanf("%lld %lld", &X, &Y);
	printf("%ld\n", upper_bound(ans.begin(), ans.end(), Y) - lower_bound(ans.begin(), ans.end(), X));
	exit(0);
}
