#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const double eps = 1e-6;

struct Square
{
	double x[4];
	double y[4];
};

Square A, B;
vector<pair<pair<double, double>, pair<double, double> > > ans;

void input(Square &X)
{
	int i, x, y;
	double tx = 0.0, ty = 0.0;
	double dx, dy;
	for(i = 0;i < 2;i += 1)
	{
		scanf("%d %d", &x, &y);
		X.x[i<<1] = x;
		X.y[i<<1] = y;
		tx += x;
		ty += y;
	}
	tx /= 2;
	ty /= 2;
	dx = X.x[0] - tx;
	dy = X.y[0] - ty;
	for(i = 0;i < 2;i += 1)
	{
		X.x[(i<<1) + 1] = tx + (i?1:-1) * (-dy);
		X.y[(i<<1) + 1] = ty + (i?1:-1) * dx;
	}
}

double cross(double x1, double y1, double x2, double y2)
{
	return x1 * y2 - y1 * x2;
}

int Sgn(double x)
{
	if(x < -eps)
		return -1;
	if(x > eps)
		return 1;
	return 0;
}

int test(double x1, double y1, double x2, double y2, double x3, double y3)
{
	return Sgn(cross(x2 - x1, y2 - y1, x3 - x1, y3 - y1));
}

bool notin(double x1, double y1, double x2, double y2)
{
	int i;
	double vx = x2 - x1, vy = y2 - y1;
	double tx1, ty1, tx2, ty2;
	for(i = 0;i < ans.size();i += 1)
	{
		tx1 = ans[i].first.first;
		tx2 = ans[i].second.first;
		ty1 = ans[i].first.second;
		ty2 = ans[i].second.second;
		//printf("test:(%f %f) (%f %f) (%f %f) (%f %f)\n", x1, y1, x2, y2, tx1, ty1, tx2, ty2);
		if(!Sgn(cross(vx, vy, tx2 - tx1, ty2 - ty1))
			&& !test(x1, y1, x2, y2, tx1, ty1))
			return false;
	}
	return true;
}

bool check(double x1, double y1, double x2, double y2)
{
	int i, sign1[4], sign2[4];
	bool on1 = false, on2 = false;
	bool pos1 = true, pos2 = true, neg1 = true, neg2 = true;
	if(fabs(x1 - x2) < eps && fabs(y1 - y2) < eps)
		return false;
	for(i = 0;i < 4;i += 1)
	{
		sign1[i] = test(x1, y1, x2, y2, A.x[i], A.y[i]);
		if(!sign1[i])
			on1 = true;
		if(sign1[i] > 0)
			neg1 = false;
		if(sign1[i] < 0)
			pos1 = false;
	}
	for(i = 0;i < 4;i += 1)
	{
		sign2[i] = test(x1, y1, x2, y2, B.x[i], B.y[i]);
		if(!sign2[i])
			on2 = true;
		if(sign2[i] > 0)
			neg2 = false;
		if(sign2[i] < 0)
			pos2 = false;
	}
	//printf("(%f %f) (%f %f) %d\n", x1, y1, x2, y2, (pos1 || neg1) && (pos2 || neg2) && on1 && on2 && notin(x1, y1, x2, y2));
	return (pos1 || neg1) && (pos2 || neg2) && on1 && on2 && notin(x1, y1, x2, y2);
}

int main()
{
	freopen("equal-squares.in", "r", stdin);
	freopen("equal-squares.out", "w", stdout);
	int i, j, same = 0;
	input(A);
	input(B);
	/*
	for(i = 0;i < 4;i += 1)
		printf("(%f, %f) ", A.x[i], A.y[i]);
	printf("\n");
	for(i = 0;i < 4;i += 1)
		printf("(%f, %f) ", B.x[i], B.y[i]);
	printf("\n");
	*/
	for(i = 0;i < 4;i += 1)
	{
		for(j = 0;j < 4;j += 1)
		{
			if(fabs(A.x[i] - B.x[j]) < eps && fabs(A.y[i] - B.y[j]) < eps)
				same += 1;
			if(check(A.x[i], A.y[i], B.x[j], B.y[j]))
				ans.push_back(make_pair(
								make_pair(A.x[i], A.y[i]),
								make_pair(B.x[j], B.y[j])
							));
			if(check(A.x[i], A.y[i], A.x[j], A.y[j]))
				ans.push_back(make_pair(
								make_pair(A.x[i], A.y[i]),
								make_pair(A.x[j], A.y[j])
							));
			if(check(B.x[i], B.y[i], B.x[j], B.y[j]))
				ans.push_back(make_pair(
								make_pair(B.x[i], B.y[i]),
								make_pair(B.x[j], B.y[j])
							));
		}
	}
	if(same == 1)
		printf("Infinity\n");
	else
		printf("%d\n", ans.size());
	exit(0);
}
