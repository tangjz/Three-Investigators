#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 81000;

int T;
int N, X, Y;
char Derek[NMAX], Alfia[NMAX];

int main()
{
	int t;
	int i, same, diff;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		same = diff = 0;
		scanf("%d %d %d", &N, &X, &Y);
		scanf("%s %s", Derek, Alfia);
		for(i = 0;i < N;i += 1)
		{
			if(Derek[i] == Alfia[i])
				same += 1;
			else
				diff += 1;
		}
		if(abs(X - Y) > diff || ((X + Y - abs(X - Y))>>1) > same + ((diff - abs(X - Y))>>1))
			printf("Lying\n");
		else
			printf("Not lying\n");
	}
	exit(0);
}
