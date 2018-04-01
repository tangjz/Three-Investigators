#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 110000, MMAX = 110000, QMAX = 110000;
const double eps = 1e-10;

struct Point
{
	double x;
	double y;
	
	operator<(Point &v)
	const{
		if(y == v.y)
			return x < v.x;
		return y < v.y;
	}
};

int N, M, Q;
double ans;
Point L[NMAX], R[MMAX], C[QMAX];

int main()
{
	int i, j, x, y;
	int l, r;
	double tmp, mini, maxi;
	ans = 3e9;
	scanf("%d", &N);
	for(i = 0;i < N;i += 1)
	{
		scanf("%d %d", &x, &y);
		L[i] = (Point){(double)x, (double)y};
	}
	scanf("%d", &M);
	for(i = 0;i < M;i += 1)
	{
		scanf("%d %d", &x, &y);
		R[i] = (Point){(double)x, (double)y};
	}
	for(l = r = 0;l < N && r < M;)
	{
		if(L[l].y < R[r].y)
		{
			ans = min(ans, (L[l].y - R[r - 1].y) / (R[r].y - R[r - 1].y) * (R[r].x - R[r - 1].x) + R[r - 1].x - L[l].x);
			l += 1;
		}
		else if(L[l].y > R[r].y)
		{
			ans = min(ans, R[r].x - ((R[r].y - L[l - 1].y) / (L[l].y - L[l - 1].y) * (L[l].x - L[l - 1].x) + L[l - 1].x));
			r += 1;
		}
		else
		{
			ans = min(ans, R[r].x - L[l].x);
			l += 1;
			r += 1;
		}
	}
	scanf("%d", &Q);
	for(i = 0;i < Q;i += 1)
	{
		scanf("%d %d", &x, &y);
		C[i] = (Point){(double)x, (double)y};
	}
	sort(C, C + Q);
	for(i = l = r = 0;i < Q && l < N && r < M;i += 1)
	{
		if(C[i].y < L[0].y)
			continue;
		while(l < N && L[l].y < C[i].y)
			l += 1;
		while(r < M && R[r].y < C[i].y)
			r += 1;
		if(l >= N || r >= M)
			break;
		tmp = 0.0;
		if(!l)
		{
			mini = L[l].x;
			maxi = R[r].x;
		}
		else
		{
			mini = (C[i].y - L[l - 1].y) / (L[l].y - L[l - 1].y) * (L[l].x - L[l - 1].x) + L[l - 1].x;
			maxi = (C[i].y - R[r - 1].y) / (R[r].y - R[r - 1].y) * (R[r].x - R[r - 1].x) + R[r - 1].x;
		}
		//printf("y:%f, [%.6f, %.6f]\n", C[i].y, mini, maxi);
		for(j = i, tmp = -1.0;j < Q && C[j].y == C[i].y;j += 1)
		{
			if(C[j].x < mini)
				continue;
			if(C[j].x > maxi)
				continue;
			tmp = max(tmp, C[j].x - (j > i?max(C[j - 1].x, mini):mini));
			if(j + 1 >= Q || C[j + 1].y != C[i].y || C[j + 1].x - maxi >= -eps)
				tmp = max(tmp, maxi - C[j].x);
		}
		if(tmp > eps)
			ans = min(ans, tmp);
		i = j - 1;
	}
	printf("%.7f\n", ans);
	exit(0);
}
