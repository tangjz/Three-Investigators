#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

struct FaceRotate
{
	int face[6];
	int corner[3];
	int edge[18];
};

struct EdgeRotate
{
	int edge[18];
};

FaceRotate fr[8];
EdgeRotate er[4];

int T;
int state[72], tmp[72];
bool flag;

bool check()
{
	int i;
	for(i = 0;i < 72;i += 1)
	{
		if(state[i] != state[i - (i % 9)])
			return false;
	}
	return true;
}

void inline loop(int x[], int len, int delta, int gap)
{
	int i;
	int b = delta > 0?0:len - 1, e = delta > 0?len:-1;
	memcpy(tmp, state, sizeof(tmp));
	for(i = b;i != e;i += delta)
		tmp[x[i] - 1] = state[x[(i + gap * delta + len) % len] - 1];
	memcpy(state, tmp, sizeof(state));
}

void faceRotate(FaceRotate &r, int delta)
{
	loop(r.face, 6, delta, 2);
	loop(r.corner, 3, delta, 1);
	loop(r.edge, 18, delta, 6);
}

void edgeRotate(EdgeRotate &r, int delta)
{
	loop(r.edge, 18, delta, 6);
}

void solve(int cur)
{
	int i;
	if(check())
		flag = true;
	if(flag)
		return;
	if(cur == 3)
		return;
	for(i = 0;i < 8 && !flag;i += 1)
	{
		faceRotate(fr[i], 1);
		solve(cur + 1);
		faceRotate(fr[i], -1);
		faceRotate(fr[i], -1);
		solve(cur + 1);
		faceRotate(fr[i], 1);
	}
	for(i = 0;i < 4 && !flag;i += 1)
	{
		edgeRotate(er[i], 1);
		solve(cur + 1);
		edgeRotate(er[i], -1);
		edgeRotate(er[i], -1);
		solve(cur + 1);
		edgeRotate(er[i], 1);
	}
}

int main()
{
	fr[0] = (FaceRotate){
		{2, 3, 4, 8, 7, 6},
		{1, 9, 5},
		{10, 12, 11, 15, 14,
		54,
		41, 42, 43, 44, 45,
		68,
		36, 35, 31, 30, 28,
		19}
	};
	fr[1] = (FaceRotate){
		{11, 12, 13, 17, 16, 15},
		{10, 18, 14},
		{19, 21, 20, 24, 23, 
		63, 
		50, 51, 52, 53, 54, 
		41, 
		9, 8, 4, 3, 1, 
		28}
	};
	fr[2] = (FaceRotate){
		{20, 21, 22, 26, 25, 24},
		{19, 27, 23},
		{28, 30, 29, 33, 32, 
		72, 
		59, 60, 61, 62, 63, 
		50, 
		18, 17, 13, 12, 10, 
		1}
	};
	fr[3] = (FaceRotate){
		{29, 30, 31, 35, 34, 33},
		{28, 36, 32},
		{68, 69, 70, 71, 72, 
		59, 
		27, 26, 22, 21, 19, 
		10, 
		1, 3, 2, 6, 5, 
		45}
	};
	fr[4] = (FaceRotate){
		{38, 39, 40, 44, 43, 42},
		{37, 45, 41},
		{5, 6, 7, 8, 9, 
		14, 
		54, 53, 49, 48, 46, 
		55, 
		64, 66, 65, 69, 68, 
		36}
	};
	fr[5] = (FaceRotate){
		{47, 48, 49, 53, 52, 51},
		{46, 54, 50},
		{37, 39, 38, 42, 41, 
		9, 
		14, 15, 16, 17, 18, 
		23, 
		63, 62, 58, 57, 55, 
		64}
	};
	fr[6] = (FaceRotate){
		{56, 57, 58, 62, 61, 60},
		{55, 63, 59},
		{46, 48, 47, 51, 50, 
		18, 
		23, 24, 25, 26, 27, 
		32, 
		72, 71, 67, 66, 64, 
		37}
	};
	fr[7] = (FaceRotate){
		{65, 66, 67, 71, 70, 69},
		{64, 72, 68},
		{55, 57, 56, 60, 59, 
		27, 
		32, 33, 34, 35, 36, 
		5, 
		45, 44, 40, 39, 37, 
		46}
	};
	er[0] = (EdgeRotate){
		{13, 17, 16, 
		52, 53, 49, 
		38, 39, 40, 
		65, 69, 70, 
		34, 33, 29, 
		22, 21, 20}
	};
	er[1] = (EdgeRotate){
		{22, 26, 25, 
		61, 62, 58, 
		47, 48, 49, 
		38, 42, 43, 
		7, 6, 2, 
		31, 30, 29}
	};
	er[2] = (EdgeRotate){
		{4, 3, 2, 
		31, 35, 34, 
		70, 71, 67, 
		56, 57, 58, 
		47, 51, 52, 
		16, 15, 11}
	};
	er[3] = (EdgeRotate){
		{65, 66, 67, 
		56, 60, 61, 
		25, 24, 20, 
		13, 12, 11, 
		4, 8, 7, 
		43, 44, 40}
	};
	int t, i;
	scanf("%d", &T);
	for(t = 0;t < T;t += 1)
	{
		flag = false;
		for(i = 0;i < 72;i += 1)
			scanf("%d", &state[i]);
		solve(0);
		printf("%s\n", flag?"YES":"NO");
	}
	exit(0);
}
