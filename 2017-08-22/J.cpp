#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int LMAX = 2600;

int T, N, M;
char A[LMAX], B[LMAX];
bool star[LMAX];
bool f[LMAX][LMAX][2];

bool match(char x, char y)
{
	if(x == '.' || y == '.')
		return true;
	return x == y;
}

int main()
{
	int t, i, j, k;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		memset(f, 0, sizeof(f));
		memset(star, 0, sizeof(star));
		scanf("%s %s", A + 1, B + 1);
		N = strlen(A + 1);
		M = strlen(B + 1);
		for(i = 1, j = 0;i <= M;i += 1)
		{
			if(B[i] == '*')
			{
				star[j] = true;
				continue;
			}
			B[++j] = B[i];
		}
		M = j;
		f[0][0][0] = true;
		for(i = 0;i <= N;i += 1)
		{
			for(j = 0;j <= M;j += 1)
			{
				for(k = 0;k < 2;k += 1)
				{
					if(!f[i][j][k])
						continue;
					//printf("f[%d][%d][%d]\n", i, j, k);
					if(j + 1 <= M)
					{
						if(i + 1 <= N)
						{
							if((!star[j + 1] || !k) && match(A[i + 1], B[j + 1]))
							{
								//printf("1 to %d %d %d\n", i + 1, j + 1, 0);
								f[i + 1][j + 1][0] = true;
							}
							if(star[j + 1] && ((k && match(A[i + 1], A[i])) || (!k && match(A[i + 1], B[j + 1]))))
							{
								//printf("2 to %d %d %d\n", i + 1, j, 1);
								f[i + 1][j][1] = true;
							}
						}
						if(star[j + 1])
						{
							//printf("3 to %d %d %d\n", i, j + 1, 0);
							f[i][j + 1][0] = true;
						}
					}
				}
			}
		}
		printf("%s\n", (f[N][M][0] || f[N][M][1])?"yes":"no");
	}
	exit(0);
}
