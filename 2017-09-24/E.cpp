#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const int BUFFERMAX = 100000;
const double eps = 1e-6;

struct Point
{
	double x;
	double y;
	double z;
};

int N, pos;
char str[BUFFERMAX];
Point norm[20];
vector<Point> face[20];
bool ans[20];

Point cross(Point a, Point b, Point c)
{
	Point u = (Point){b.x - a.x, b.y - a.y, b.z - a.z};
	Point v = (Point){c.x - a.x, c.y - a.y, c.z - a.z};
	return (Point){u.y * v.z - u.z * v.y, -(u.x * v.z - u.z * v.x), u.x * v.y - u.y * v.x};
}

double dot(Point a, Point b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

bool input(double &x)
{
	bool flag = sscanf(str + pos, "%lf", &x) != EOF;
	bool init = true;
	if(flag)
	{
		while(*(str + pos))
		{
			if(*(str + pos) != ' ')
				init = false;
			else if(!init)
				break;
			pos += 1;
		}
	}
	return flag;
}

int sgn(double x)
{
	if(x > eps)
		return 1;
	if(x < -eps)
		return -1;
	return 0;
}

bool check(int id, Point u)
{
	int f = (id == 1?2:1), i;
	double t1, t2;
	Point v;
	u = (Point){u.x - face[id][0].x, u.y - face[id][0].y, u.z - face[id][0].z};
	t1 = dot(norm[id], u);
	if(fabs(t1) < eps)
		return false;
	for(i = 0;i < face[f].size();i += 1)
	{
		v = (Point){face[f][i].x - face[id][0].x, face[f][i].y - face[id][0].y, face[f][i].z - face[id][0].z};
		t2 = dot(norm[id], v);
		if(fabs(t2) > eps)
			break;
	}
	return sgn(t1) * sgn(t2) < 0;
}

int main()
{
	int i, id;
	double x, y, z;
	scanf("%d", &N);
	for(i = 0;i < N;i += 1)
	{
		scanf("%d", &id);
		gets(str);
		pos = 0;
		while(input(x) && input(y) && input(z))
			face[id].push_back((Point){x, y, z});
		norm[id] = cross(face[id][0], face[id][1], face[id][2]);
	}
	scanf("%lf %lf %lf", &x, &y, &z);
	for(i = 1;i <= N;i += 1)
	{
		if(check(i, (Point){x, y, z}))
			printf("%d\n", i);
	}
	exit(0);
}
