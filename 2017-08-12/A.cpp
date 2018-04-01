#include <bitset>
#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 1001, BLEN = 18;
const LL BASE = (LL)1e18;
int T, N;
std::bitset<maxn> A, X, B, Y;
void read(std::bitset<maxn> &ret) {
	int len = 0, slen;
	static char buf[maxn];
	static LL num[maxn];
	scanf("%s", buf);
	slen = strlen(buf);
	for(int R = slen; R > 0; R -= BLEN) {
		int L = R - BLEN < 0 ? 0 : R - BLEN;
		buf[R] = '\0';
		sscanf(buf + L, "%I64d", num + (len++));
	}
	--num[0];
	for(int i = 0; i < len; ++i)
		if(num[i] < 0) {
			num[i] += BASE;
			--num[i + 1];
		}
	if(len > 1 && !num[len - 1])
		--len;
	ret.reset();
	for(int i = 0; i < N; ++i) {
		int rem = 0;
		for(int j = len - 1; j >= 0; --j) {
			LL tmp = (rem ? BASE : 0) + num[j];
			num[j] = tmp >> 1;
			rem = tmp & 1;
		}
		for( ; len > 1 && !num[len - 1]; --len);
		if(rem)
			ret.set(i);
	}
}
int main() {
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		scanf("%d", &N), read(A), read(X), read(B), read(Y);
		A ^= B;
		X ^= Y;
		bool chk = 0;
		for(int i = 1; i <= N; ++i) {
			if(A == X) {
				chk = 1;
				break;
			}
			if(X.test(0))
				X.set(N);
			X >>= 1;
		}
		printf("Case %d: %s\n", Case, chk ? "Yes" : "No");
	}
	return 0;
}
