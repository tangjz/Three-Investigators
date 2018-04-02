#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

int T;
char zodiac[12][10] = {
	"rat",
	"ox",
	"tiger",
	"rabbit",
	"dragon",
	"snake",
	"horse",
	"sheep",
	"monkey",
	"rooster",
	"dog",
	"pig"
};

int id(char x[])
{
	int i = 0;
	for(i = 0;i < 12;i += 1)
	{
		if(!strcmp(zodiac[i], x))
			return i;
	}
	return -1;
}

int main()
{
	int t, x, y;
	char A[10], B[10];
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		scanf("%s %s", A, B);
		x = id(A);
		y = id(B);
		if(x == y)
			printf("12\n");
		else
			printf("%d\n", (y - x + 12) % 12);
	}
	exit(0);
}
