#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 51000, MMAX = 110;

int T;
int N, M, K;
long long ans;
int mat[MMAX][MMAX];
char strS[NMAX], revS[NMAX];
char strT[MMAX], revT[MMAX];
int cntLeft[NMAX], cntRight[NMAX];
int leftFail[NMAX], rightFail[NMAX];
long long sumLeft[NMAX], sumRight[NMAX];
int posLeft[NMAX], posRight[NMAX];
long long leftVec[NMAX][MMAX], rightVec[NMAX][MMAX];

void buildKMP(char str[], int len, int fail[])
{
	int i, j;
	for(i = 2, j = 0;i <= len;i += 1)
	{
		while(j && str[j + 1] != str[i])
			j = fail[j];
		if(str[j + 1] == str[i])
			j += 1;
		fail[i] = j;
	}
}

void buildMat()
{
	int i, j, k, pos;
	for(i = 0;i < M;i += 1)
	{
		for(j = 0;j < M;j += 1)
		{
			for(k = j, pos = i;k;k -= 1)
			{
				while(pos && strT[pos + 1] != revT[k])
					pos = leftFail[pos];
				if(strT[pos + 1] == revT[k])
					pos += 1;
				if(pos == M)
					mat[i][j] += 1;
			}
		}
	}
}

void solve(char S[], char T[], int fail[], int cnt[], long long sum[], int pos[])
{
	int i, cur;
	for(i = 1, cur = 0;i <= N;i += 1)
	{
		cnt[i] = cnt[i - 1];
		sum[i] = sum[i - 1];
		while(cur && S[i] != T[cur + 1])
			cur = fail[cur];
		if(S[i] == T[cur + 1])
			cur += 1;
		if(cur == M)
		{
			cnt[i] += 1;
			sum[i] += N - i + 1;
			cur = fail[cur];
		}
		pos[i] = cur;
	}
}

int main()
{
	int t, i, j, l, r;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		memset(mat, 0, sizeof(mat));
		memset(leftFail, 0, sizeof(leftFail));
		memset(rightFail, 0, sizeof(rightFail));
		memset(posLeft, 0, sizeof(posLeft));
		memset(posRight, 0, sizeof(posRight));
		memset(leftVec, 0, sizeof(leftVec));
		memset(rightVec, 0, sizeof(rightVec));
		memset(sumLeft, 0, sizeof(sumLeft));
		memset(sumRight, 0, sizeof(sumRight));
		memset(cntLeft, 0, sizeof(cntLeft));
		memset(cntRight, 0, sizeof(cntRight));
		memset(revT, 0, sizeof(revT));
		memset(revS, 0, sizeof(revS));
		memset(strT, 0, sizeof(strT));
		memset(strS, 0, sizeof(strS));
		scanf("%d %d %d", &N, &M, &K);
		for(i = 1;i <= N;i += 1)
		{
			scanf(" %c", &strS[i]);
			revS[1 + N - i] = strS[i];
		}
		for(i = 1;i <= M;i += 1)
		{
			scanf(" %c", &strT[i]);
			revT[1 + M - i] = strT[i];
		}
		buildKMP(strT, M, leftFail);
		buildKMP(revT, M, rightFail);
		buildMat();
		solve(strS, strT, leftFail, cntLeft, sumLeft, posLeft);
		solve(revS, revT, rightFail, cntRight, sumRight, posRight);
		for(i = 1;i <= N;i += 1)
		{
			for(j = 1;j < M;j += 1)
				leftVec[i][j] = leftVec[i - 1][j];
			leftVec[i][posLeft[i]] += 1;
		}
		for(i = 1;i <= N;i += 1)
		{
			for(j = 0;j < M;j += 1)
				rightVec[i][j] = rightVec[i - 1][j] + mat[j][posRight[i]];
		}
		for(i = 1;i <= K;i += 1)
		{
			scanf("%d %d", &l, &r);
			ans = 0;
			ans += (sumLeft[l] - (long long)(N - l) * cntLeft[l]) * (N - r + 1);
			ans += (sumRight[N + 1 - r] - (long long)(r - 1) * cntRight[N + 1 - r]) * l;
			for(j = 0;j < M;j += 1)
				ans += leftVec[l][j] * rightVec[N + 1 - r][j];
			printf("%lld\n", ans);
		}
	}
	exit(0);
}
