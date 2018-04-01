#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define M 1000000007
#define all(a) a.begin(), a.end()

const double pi = acos(-1.0);
//also typedef complex<double> Comp;
struct Comp{
  double x, y;
  Comp(): x(0), y(0) {}
  Comp(double _x, double _y): x(_x), y(_y) {}
  Comp operator + (const Comp &rhs) const {
    return Comp(x + rhs.x, y + rhs.y);
  }
  Comp operator - (const Comp &rhs) const {
    return Comp(x - rhs.x, y - rhs.y);
  }
  Comp operator * (const Comp &rhs) const {
    return Comp(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);
  }
  Comp &operator += (const Comp &rhs) {
    x += rhs.x; y += rhs.y;
    return *this;
  }
  Comp &operator -= (const Comp &rhs) {
    x -= rhs.x; y -= rhs.y;
    return *this;
  }
  Comp conj() const {
    return Comp(x, -y);
  }
};
const int MAXN = 262144 << 1;
Comp X[MAXN], Y[MAXN], Z[MAXN];
int bitrev[MAXN];
int A[2][MAXN], B[2][MAXN], f[MAXN], g[MAXN];
int n, m;
int a[MAXN], b[MAXN], p[MAXN];
char s[12];

void FFT(Comp A[], int n, int o){
	for(int i = 0; i < n; i++) if(bitrev[i] < i) swap(A[bitrev[i]], A[i]);
	for(int s = 0; 1 << s <= n; s++){
		int m = 1 << s;
		double ang = 2 * pi / m * o;
		Comp od = Comp(cos(ang), sin(ang));
		for(int k = 0; k < n; k += m){
			Comp w = Comp(1.0, 0);
			for(int j = 0; j < m / 2; j++){
				Comp t = w * A[k + j + m / 2];
				A[k + j + m / 2] = A[k + j] - t;
				A[k + j] = A[k + j] + t;
				w = w * od;
			}
		}
	}
}

void conv(int x[], int n, int y[], int m, int z[]){
  int l = 0;
  while ((1 << l) < n + m - 1) ++l;
  int s = 1 << l;
  for (int i = 0; i < s; ++i)
    bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (l - 1));
  for (int i = 0; i < s; ++i){
		X[i] = Comp(i < n ? x[i] : 0, 0);
		Y[i] = Comp(i < m ? y[i] : 0, 0);
  }
  FFT(X, s, 1); FFT(Y, s, 1);
	for(int i = 0; i < s; ++i) Z[i] = X[i] * Y[i];
  FFT(Z, s, -1);
  for (int i = 0; i < s; ++i)
		z[i] = int(Z[i].x / s + 0.5);
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i){
		scanf("%s", s);
		for(int j = 0; j < 7; ++j) a[i] = a[i] << 1 | (s[j] == '1');
		A[s[7] - '0'][i - 1] = 1;
	}
	for(int i = 1; i <= m; ++i){
		scanf("%s", s);
		for(int j = 0; j < 7; ++j) b[i] = b[i] << 1 | (s[j] == '1');
		B[s[7] - '0'][m - i] = 1;
	}
	conv(A[0], n, B[1], m, f);
	conv(A[1], n, B[0], m, g);

	int ans = 1e9, wans = -1;
	bool flag = 0;
	int j = 0;
	for(int i = 2; i <= m; ++i){
		while(j && b[j + 1] != b[i]) j = p[j];
		if(b[j + 1] == b[i]) ++j;
		p[i] = j;
	}
	
	j = 0;
	for(int i = 1; i <= n; ++i){
		while(j && b[j + 1] != a[i]) j = p[j];
		if(b[j + 1] == a[i]) ++j;
		if(j == m){
			flag = 1;
			int tmp = f[i - 1] + g[i - 1];
			if(tmp < ans) ans = tmp, wans = i;
			j = p[j];
		}
	}
	
	if(flag) printf("Yes\n%d %d\n", ans, wans - m + 1);
	else printf("No\n");
	

	return 0;
}
