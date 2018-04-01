#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = (int)1e9 + 7;
int mod_inv(int x) {
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
void mod_inc_mul(int &x, int y, int z) {
	x = (x + (LL)y * z) % mod;
}
struct Matrix {
	int num[2][2];
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {};
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				for(int k = 0; k < 2; ++k)
					mod_inc_mul(ret.num[i][k], num[i][j], t.num[j][k]);
		return ret;
	}
	Matrix pow(int k) const {
		Matrix ret = (Matrix){1, 0, 0, 1}, tmp = *this;
		while(k > 0) {
			if(k & 1)
				ret = ret * tmp;
			tmp = tmp * tmp;
			k >>= 1;
		}
		return ret;
	}
} A;
int main() {
	int t, p, q, k;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &p, &q, &k);
		p = (LL)q * mod_inv(p) % mod;
		(q = 1 - p) < 0 && (q += mod);
		A = (Matrix){q, p, p, q};
		printf("%d\n", A.pow(k).num[0][0]);
	}
	return 0;
}

