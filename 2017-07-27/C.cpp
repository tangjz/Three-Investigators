#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 260000, MOD = 1000000007;
const int INF = ~0u>>1;

int N;
int A[NMAX], B[NMAX];
int sufA[NMAX], ans;
int sufDeltaMax[NMAX];

int main()
{
	int i;
	int curSufDeltaMax;
	while(scanf("%d", &N) != EOF)
	{
		ans = 0;
		curSufDeltaMax = -INF;
		for(i = 1;i <= N;i += 1)
			scanf("%d", &A[i]);
		for(i = 1;i <= N;i += 1)
			scanf("%d", &B[i]);
		sufDeltaMax[N] = A[N] - N;
		for(i = N - 1;i;i -= 1)
			sufDeltaMax[i] = max(A[i] - i, sufDeltaMax[i + 1]);
		sort(B + 1, B + N + 1);
		for(i = 1;i <= N;i += 1)
		{
			sufA[i] = max(sufDeltaMax[B[i]], curSufDeltaMax);
			curSufDeltaMax = max(curSufDeltaMax, sufA[i] - N - i);
			ans = (ans + sufA[i]) % MOD;
		}
		printf("%d\n", ans);
	}
	exit(0);
}
