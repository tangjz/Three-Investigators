#include <cstdio>
typedef long long LL;
const int mod = 998244353;
int n;
struct Matrix {
	int num1, num2;
	Matrix operator * (Matrix const &x) const {
		return (Matrix){(int)(((LL)num1 * x.num1 + (LL)num2 * x.num2) % mod),
		(int)(((LL)num1 * x.num2 + (LL)num2 * (x.num1 + x.num2)) % mod)};
	}
	Matrix pow(int k) {
		Matrix ret = (Matrix){1, 0}, tmp = *this;
		while(k) {
			if(k & 1)
				ret = ret * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return ret;
	}
} A = {0, 1};
int main() {
	while(scanf("%d", &n) == 1) {
		int ans = A.pow((n << 1) + 3).num2 - 1;
		ans < 0 && (ans += mod);
		printf("%d\n", ans);
	}
	return 0;
}
