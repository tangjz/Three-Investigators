#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001, maxm = 10001;
int n, m, q, sqn, a[maxn], b[maxn], pos[maxn];
struct Block {
	int pre, nxt;
	int sta, len;
	bool rev;
	void access() {
		if(rev) {
			int *A = a + sta;
			std::reverse(A, A + len);
			rev = 0;
		}
	}
	void sort() {
		int *A = a + sta, *B = b + sta;
		memcpy(B, A, len * sizeof(int));
		std::sort(B, B + len);
	}
	int query(int L, int R, int val) {
		access();
		int *A = a + sta, ret = 0;
		for( ; L < R; ret += A[L++] < val);
		return ret;
	}
	int query(int val) {
		int *B = b + sta;
		return std::lower_bound(B, B + len, val) - B;
	}
} f[maxm];
void update(int idx, int sta, int len) {
	int *P = pos + sta;
	for(int i = 0; i < len; ++i)
		P[i] = idx;
}
void rebuild(bool fir = 0) { // f[0] (left) <-> ... <-> f[1] (right)
	if(!fir) {
		for(int i = f[0].nxt, idx = 0; i != 1; i = f[i].nxt) {
			f[i].access();
			memcpy(b + idx, a + f[i].sta, f[i].len * sizeof(int));
			idx += f[i].len;
		}
		memcpy(a, b, n * sizeof(int));
	}
	m = 2;
	f[0] = (Block){0, 1, 0, 0, 0};
	f[1] = (Block){0, 1, n, 0, 0};
	for(int i = 0; i < n; i += sqn) {
		int sta = i, len = std::min(sqn, n - i);
		f[m] = (Block){f[1].pre, 1, sta, len, 0};
		f[f[1].pre].nxt = m;
		f[1].pre = m;
		update(m, sta, len);
		f[m++].sort();
	}
}
void split(int idx, int sz) {
	f[m].pre = idx;
	f[m].nxt = f[idx].nxt;
	f[f[idx].nxt].pre = m;
	f[idx].nxt = m;
	f[idx].access();
	f[m].sta = f[idx].sta + sz;
	f[m].len = f[idx].len - sz;
	update(m, f[m].sta, f[m].len);
	f[idx].len = sz;
	f[idx].sort();
	f[m++].sort();
}
void align(int L, int R) {
	int pL = pos[L];
	if(f[pL].sta < L)
		split(pL, L - f[pL].sta);
	int pR = pos[R];
	if(R - f[pR].sta + 1 < f[pR].len)
		split(pR, R - f[pR].sta + 1);
}
void convert(int &L, int &R) { // order -> index
	int cnt = 0;
	bool fL = 0;
	for(int i = f[0].nxt; i != 1; i = f[i].nxt) {
		cnt += f[i].len;
		if(!fL && L <= cnt) {
			L = f[i].sta + f[i].len - 1 - (cnt - L);
			fL = 1;
		}
		if(R <= cnt) {
			R = f[i].sta + f[i].len - 1 - (cnt - R);
			break;
		}
	}
}
int main() {
	while(scanf("%d", &n) == 1) {
		for(sqn = 1; sqn * sqn <= n << 2; ++sqn);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		rebuild(1);
		scanf("%d", &q);
		while(q--) {
			char op[9];
			scanf("%s", op);
			if(op[0] == 'R') {
				int L, R;
				scanf("%d%d", &L, &R);
				convert(L, R);
				align(L, R);
				for(int pL = pos[L], pR = f[pos[R]].nxt; pL != pR; pL = f[pL].pre) {
					f[pL].rev = !f[pL].rev;
					std::swap(f[pL].pre, f[pL].nxt);
				}
				std::swap(f[f[pos[L]].nxt].nxt, f[f[pos[R]].pre].pre);
				std::swap(f[pos[L]].nxt, f[pos[R]].pre);
			} else if(op[0] == 'S') {
				int L1, R1, L2, R2;
				scanf("%d%d%d%d", &L1, &R1, &L2, &R2);
				convert(L1, R1);
				convert(L2, R2);
				align(L1, R1);
				align(L2, R2);
				std::swap(f[pos[L1]].pre, f[pos[L2]].pre);
				std::swap(f[f[pos[L1]].pre].nxt, f[f[pos[L2]].pre].nxt);
				std::swap(f[pos[R1]].nxt, f[pos[R2]].nxt);
				std::swap(f[f[pos[R1]].nxt].pre, f[f[pos[R2]].nxt].pre);
			} else { // op[0] == 'A'
				int L, R, k;
				scanf("%d%d%d", &L, &R, &k);
				convert(L, R);
				int ans, pL = pos[L], pR = pos[R];
				if(pL == pR) {
					ans = f[pL].query(L - f[pL].sta, R - f[pR].sta + 1, k);
				} else {
					ans = f[pL].query(L - f[pL].sta, f[pL].len, k) + f[pR].query(0, R - f[pR].sta + 1, k);
					for(pL = f[pL].nxt; pL != pR; pL = f[pL].nxt)
						ans += f[pL].query(k);
				}
				printf("%d\n", ans);
			}
			if(m > sqn * 2)
				rebuild();
		}
	}
	return 0;
}
