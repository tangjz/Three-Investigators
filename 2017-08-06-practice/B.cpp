#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const double pi = acos(-1.0);

const int N = 2;
struct matrix{
	int n, m;
	double x[N][N];
	matrix() {}
	matrix(int n, int m) : n(n), m(m){
		memset(x, 0, sizeof(x));
	}
	matrix operator * (const matrix &R) const{
		matrix res(n, R.m);
		for(int i = 0; i < m; ++i)
			for(int j = 0; j < n; ++j)
				for(int k = 0; k < R.m; ++k)
					res.x[j][k] += x[j][i] * R.x[i][k];
		return res;
	}
	matrix operator - (const matrix &R) const{
		assert(n == R.n && m == R.m);
		matrix res(n, m);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				res.x[i][j] = x[i][j] - R.x[i][j];
		return res;
	}
	matrix operator + (const matrix &R) const{
		assert(n == R.n && m == R.m);
		matrix res(n, m);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				res.x[i][j] = x[i][j] + R.x[i][j];
		return res;
	}
	void reset(){
		assert(n == m);
		memset(x, 0, sizeof(x));
		for(int i = 0; i < n; ++i) x[i][i] = 1;
	}
};

int T, n;

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		matrix A(2, 2), B(2, 1); A.reset();
		matrix T(2, 1);
		
		for(int i = 0; i < n; ++i){
			static double x, y, p;
			scanf("%lf%lf%lf", &x, &y, &p);
			matrix a(2, 2), b(2, 1);
			a.x[0][0] = cos(-p), a.x[0][1] = sin(-p);
			a.x[1][0] = -sin(-p), a.x[1][1] = cos(-p);
			b.x[0][0] = x, b.x[1][0] = y;
			
			A = a * A;
			B = a * (B - b) + b;
			
			T = a * (T - b);
			T = T + b;
		}
		
		double p = -atan2(A.x[0][1], A.x[0][0]);
		matrix C(2, 2); C.reset(); C = C - A;
		matrix D(2, 2); 
		double CC = C.x[0][0] * C.x[1][1] - C.x[0][1] * C.x[1][0];
		D.x[0][0] = C.x[1][1] / CC;
		D.x[0][1] = -C.x[0][1] / CC;
		D.x[1][0] = -C.x[1][0] / CC;
		D.x[1][1] = C.x[0][0] / CC;
		B = D * B;
		if(p < 0) p += 2 *pi;
		printf("%.8lf %.8lf %.8lf\n", B.x[0][0], B.x[1][0], p);
	}
	return 0;
}
