#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 21000;

int N;
long long A[NMAX], B[NMAX], C[NMAX];

int main()
{
	int i;
	long long l, r, mid, tmp;
	while(scanf("%d", &N) != EOF)
	{
		tmp = 0;
		for(i = 1;i <= N;i += 1)
		{
			scanf("%lld %lld %lld", &A[i], &B[i], &C[i]);
			if(!A[i])
				A[i] += C[i];
			if(A[i] <= B[i])
				tmp ^= ((B[i] - A[i] + C[i]) / C[i]) & 1;
			//printf("tmp: %lld\n", tmp);
		}
		if(!tmp)
			printf("DC Qiang is unhappy.\n");
		else
		{
			l = 0;
			r = 1LL<<32;
			while(l + 1 < r)//[l, r)
			{
				mid = (l + r)>>1;
				tmp = 0;
				//printf("mid: %lld\n", mid);
				for(i = 1;i <= N;i += 1)
				{
					if(mid >= A[i] && A[i] <= B[i])
						tmp ^= ((min(mid, B[i]) - A[i] + C[i]) / C[i]) & 1;
				}
				if(tmp)
					r = mid;
				else
					l = mid;
			}
			tmp = 0;
			for(i = 1;i <= N;i += 1)
			{
				if(A[i] <= r && r <= B[i] && A[i] <= B[i])
					tmp += (r - A[i]) % C[i]?0:1;
			}
			printf("%lld %lld\n", r, tmp);
		}
	}
	exit(0);
}
