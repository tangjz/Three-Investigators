#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

#define B 16 //BÎª¾ØÕó´óÐ¡
#define M 1000000007

struct matrix{
	int x[B][B];
	int *operator [] (int a) { return x[a]; }
	void clear(){
		memset(x, 0, sizeof(x));
	}
	void reset(){
		memset(x, 0, sizeof(x));
		for(int i = 0; i < B; ++i) x[i][i] = 1;
	}
}p, base[70];
inline void inc(int &a, int b) { (a += b, a >= M) && (a -= M); }
matrix operator * (matrix &a, matrix &b){
	memset(p.x, 0, sizeof(p.x));
	static int i, j, k;
	for(i = 0; i < B; i++)
		for(j = 0; j < B; j++)
			for(k = 0; k < B; k++)
				inc(p[i][j], (ll)a[i][k] * b[k][j] % M);
	return p;
}

ll n;
int res[B], tmp[B];

int main(){
	matrix A; A.clear();
	for(int mask = 0; mask < 16; ++mask){
		for(int fmask = 0; fmask < 3 * 3 * 3 * 3; ++fmask){
			int pmask = mask;
			int t = fmask; bool flag = 1; int tmask = 0;
			for(int i = 0; i < 4 && flag; ++i){
				int f = t % 3; t /= 3;
				if(f && (pmask >> i & 1)) flag = 0;
				if(f == 1 && (i == 3 || (pmask >> (i + 1) & 1))) flag = 0;
				
				if(f == 1) pmask |= 1 << i, pmask |= 1 << (i + 1);
				if(f == 2) pmask |= 1 << i, tmask |= 1 << i;
			}
			if(!flag) continue;
			if(pmask != 15) continue;
			++A[tmask][mask];
		}
	}
	base[0] = A;
	for(int i = 1; i <= 60; ++i)
		base[i] = base[i - 1] * base[i - 1];
	while(~scanf("%lld", &n)){
		memset(res, 0, sizeof(res)); res[0] = 1;
		for(int i = 0, j, k; i <= 60; ++i)
			if(n >> i & 1){
				memset(tmp, 0, sizeof(tmp));
				for(j = 0; j < B; ++j)
					for(k = 0; k < B; ++k)
						inc(tmp[j], (ll)base[i][j][k] * res[k] % M);
				memcpy(res, tmp, sizeof(tmp));
			}
		printf("%d\n", res[0]);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
