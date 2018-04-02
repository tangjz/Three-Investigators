#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

namespace fastIO {
	#define BUF_SIZE 100000
	//fread -> read
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void read(int &x) {
		char ch;
		while(blank(ch = nc()));
		if(IOerror)
			return;
		for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
	}
	#undef BUF_SIZE
}
using namespace fastIO;

const int NMAX = 1100000;

int N, ans, choice;
int A[NMAX], B[NMAX];

int main()
{
	int i, j, res, cnt;
	while(read(N), !fastIO::IOerror)
	{
		ans = 0;
		choice = 0;
		for(i = 0;i < N;i += 1)
			read(A[i]);
		for(i = 0;i < N;i += 1)
			read(B[i]);
		for(i = 0;i < N;i += 1)
		{
			res = 0;
			cnt = 0;
			for(j = 0;j < N;j += 1)
			{
				res += A[(i + j) % N];
				cnt += A[(i + j) % N] - B[(i + j) % N];
				if(cnt < 0)
					break;
			}
			if(ans < res)
			{
				ans = res;
				choice = i;
			}
			i += j;
		}
		printf("%d\n", choice);
	}
	exit(0);
}
