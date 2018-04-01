#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

int N, M;
vector<int> A, B;

bool check(int x)
{
	int i, j, k, depth, tmp, left = 1;
	for(i = j = depth = 0;left;depth += 1)
	{
		for(;j < x && B[x - j - 1] == depth && left;j += 1, left -= 1);
		if(j >= x)
			return true;
		for(k = tmp = 0;k < left && i + k < N && tmp + left <= N + M;k += 1)
			tmp += A[i + k];
		i += k;
		left += tmp - k;
	}
	return false;
}

bool cmp(const int &a, const int &b)
{
	return a > b;
}

int main()
{
	int i, x;
	int l, r, m;
	scanf("%d %d", &N, &M);
	for(i = 0;i < N;i += 1)
	{
		scanf("%d", &x);
		A.push_back(x);
	}
	for(i = 0;i < M;i += 1)
	{
		scanf("%d", &x);
		B.push_back(x);
	}
	sort(A.begin(), A.end(), cmp);
	sort(B.begin(), B.end(), cmp);
	for(l = 0, r = M + 1;l + 1 < r;)//[, )
	{
		m = (l + r)>>1;
		if(check(m))
			l = m;
		else
			r = m;
	}
	printf("%d\n", l);
	exit(0);
}
