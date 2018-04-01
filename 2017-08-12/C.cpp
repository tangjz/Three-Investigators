#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

const int NMAX = 510;

int N, M, tot;
int star[NMAX][2];
bool in[NMAX];
priority_queue<pair<int, pair<int, int> > > Q;
map<pair<pair<int, int>, long long>, int> Hash;
map<pair<int, int>, int> cnt;

pair<int, int> norm(int i, int j)
{
	int d;
	d = __gcd(abs(star[i][0] - star[j][0]), abs(star[i][1] - star[j][1]));
	if(star[i][1] - star[j][1] < 0)
		d = -d;
	else if(star[i][1] - star[j][1] == 0 && star[i][0] - star[j][0] < 0)
		d = -d;
	return make_pair(-(star[i][1] - star[j][1]) / d, (star[i][0] - star[j][0]) / d);
}

long long dot(pair<int, int> a, pair<int, int> b)
{
	return (long long)a.first * b.first + (long long)a.second * b.second;
}

bool check(int x)
{
	int n = sqrt(2 * x);
	return n * (n + 1) / 2 == x;
}

int main()
{
	int i, j, x, y, tmp;
	long long delta;
	pair<int, int> n;
	while(scanf("%d %d", &N, &M) != EOF)
	{
		tot = 0;
		while(!Q.empty())
			Q.pop();
		Hash.clear();
		cnt.clear();
		memset(in, 0, sizeof(in));
		for(i = 1;i <= N;i += 1)
			scanf("%d %d", &star[i][0], &star[i][1]);
		for(i = 1;i <= M; i += 1)
		{
			scanf("%d %d", &y, &x);
			y = 1 - y;
			in[x] = y?true:false;
			//printf("tot: %d\n", tot);
			for(j = 1;j <= N;j += 1)
			{
				if(j == x || !in[j])
					continue;
				if(star[j][0] == star[x][0] && star[j][1] == star[x][1])
					break;
			}
			if(j > N)
			{
				tot += y?1:-1;
				for(j = 1;j <= N;j += 1)
				{
					if(j == x || !in[j])
						continue;
					n = norm(x, j);
					//printf("x:(%d, %d) j:(%d, %d): (%d, %d)\n", star[x][0], star[x][1], star[j][0], star[j][1], n.first, n.second);
					delta = dot(n, make_pair(star[x][0], star[x][1]));
					tmp = Hash[make_pair(n, delta)] += y?1:-1;
					if(check(tmp))
					{
						if(y)
						{
							//printf("cnt + 1\n");
							tmp = cnt[n] += 1;
							Q.push(make_pair(tmp, n));
						}
						else
						{
							//printf("cnt - 1\n");
							tmp = cnt[n] -= 1;
							Q.push(make_pair(tmp, n));
						}
					}
				}
			}
			while(!Q.empty())
			{
				tmp = Q.top().first;
				n = Q.top().second;
				if(cnt[n] != tmp)
					Q.pop();
				else
					break;
			}
			if(Q.empty())
				printf("%d\n", tot);
			else
				printf("%d\n", tot - tmp);
		}
		printf("\n");
	}
	exit(0);
}
