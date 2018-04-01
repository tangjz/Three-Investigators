#include <cstdio>
#include <algorithm>
int t, n, m;
template<class T> void write(T x, char endc = '\0') {
	int len = 0;
	char buf[41];
	for( ; x > 0; x /= 10)
		buf[len++] = '0' + (x % 10);
	if(!len)
		buf[len++] = '0';
	for( ; len-- > 0; putchar(buf[len]));
	if(endc)
		putchar(endc);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		int fz = m;
		__int128 fm = 1, tp = n;
		for(--m; m > 0; m >>= 1, tp *= tp)
			(m & 1) && (fm *= tp);
		int r = std::__gcd(fz, (int)(fm % fz));
		fz /= r;
		fm /= r;
		write(fz, '/');
		write(fm, '\n');
	}
	return 0;
}
