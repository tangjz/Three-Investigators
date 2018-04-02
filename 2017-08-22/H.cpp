#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 210000;

int N, M;
long long A[NMAX];
priority_queue<long long, vector<long long>, greater<long long> > Q, delQ;

int main()
{
	int i, j;
	long long x;
	while(scanf("%d", &M) != EOF)
	{
		while(!Q.empty())
			Q.pop();
		while(!delQ.empty())
			delQ.pop();
		N = sqrt(2 * M);
		for(i = 1;i <= M;i += 1)
		{
			scanf("%lld", &x);
			Q.push(x);
		}
		printf("%d\n", N);
		for(i = 1;i <= N;i += 1)
		{
			while(!delQ.empty() && Q.top() == delQ.top())
			{
				delQ.pop();
				Q.pop();
			}
			A[i] = Q.top();
			Q.pop();
			for(j = 1;j < i;j += 1)
				delQ.push(A[i] + A[j]);
			printf("%lld%c", A[i], " \n"[i == N?1:0]);
		}
	}
	exit(0);
}
