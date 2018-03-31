#include <cmath>
#include <cstdio>
typedef double DB;
const int maxn = 222223, maxs = 5;
const DB eps = 1e-10;
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
inline int dcmp(DB x, DB y) {
	return sgn(x - y);
}
inline void readDB(DB &x) {
	double t;
	scanf("%lf", &t);
	x = t;
}
inline void writeDB(DB x, char endc = '\0') {
	printf("%.5f", (double)x);
	if(endc)
		putchar(endc);
}
inline DB sqr(DB x) {
	return x * x;
}
inline DB norm(DB x, DB y, DB z) {
	return sqrt(sqr(x) + sqr(y) + sqr(z));
}
int n, m, vec[maxn][maxs];
DB len[maxn << 1 | 1], tag[maxn << 1 | 1];
struct Matrix {
	DB num[maxs][maxs];
	bool operator == (Matrix const &t) const {
		for(int i = 1; i < maxs; ++i)
			for(int j = 1; j < maxs; ++j)
				if(dcmp(num[i][j], t.num[i][j]))
					return 0;
		return 1;
	}
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {};
		for(int i = 1; i < maxs; ++i)
			for(int j = 1; j < maxs; ++j) if(sgn(num[i][j]))
				for(int k = 1; k < maxs; ++k) if(sgn(t.num[j][k]))
					ret.num[i][k] += num[i][j] * t.num[j][k];
		return ret;
	}
} I, tr[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_init(int L, int R) {
	int rt = seg_idx(L, R);
	tag[rt] = 1;
	tr[rt] = I;
	if(L == R) {
		len[rt] = L + 1 <= n ? norm(vec[L][1] - vec[L + 1][1], vec[L][2] - vec[L + 1][2], vec[L][3] - vec[L + 1][3]) : 0;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_init(L, M);
	seg_init(M + 1, R);
	len[rt] = len[lch] + len[rch];
}
void seg_tr(int L, int R, int l, int r, Matrix &prd) {
	int rt = seg_idx(L, R);
	if(l <= L && R <= r) {
		tr[rt] = tr[rt] * prd;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(!(tr[rt] == I)) {
		tr[lch] = tr[lch] * tr[rt];
		tr[rch] = tr[rch] * tr[rt];
		tr[rt] = I;
	}
	if(l <= M)
		seg_tr(L, M, l, r, prd);
	if(M < r)
		seg_tr(M + 1, R, l, r, prd);
}
Matrix &seg_que(int L, int R, int x) {
	int rt = seg_idx(L, R);
	while(L < R) {
		int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
		if(!(tr[rt] == I)) {
			tr[lch] = tr[lch] * tr[rt];
			tr[rch] = tr[rch] * tr[rt];
			tr[rt] = I;
		}
		if(x <= M) {
			R = M;
			rt = lch;
		} else {
			L = M + 1;
			rt = rch;
		}
	}
	return tr[rt];
}
void seg_upd(int L, int R, int x, DB v) {
	int rt = seg_idx(L, R);
	if(L == R) {
		len[rt] = v;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(dcmp(tag[rt], 1)) {
		len[lch] *= tag[rt];
		len[rch] *= tag[rt];
		tag[lch] *= tag[rt];
		tag[rch] *= tag[rt];
		tag[rt] = 1;
	}
	if(x <= M)
		seg_upd(L, M, x, v);
	else
		seg_upd(M + 1, R, x, v);
	len[rt] = len[lch] + len[rch];
}
void seg_mul(int L, int R, int l, int r, DB prd) {
	int rt = seg_idx(L, R);
	if(l <= L && R <= r) {
		len[rt] *= prd;
		tag[rt] *= prd;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(dcmp(tag[rt], 1)) {
		len[lch] *= tag[rt];
		len[rch] *= tag[rt];
		tag[lch] *= tag[rt];
		tag[rch] *= tag[rt];
		tag[rt] = 1;
	}
	if(l <= M)
		seg_mul(L, M, l, r, prd);
	if(M < r)
		seg_mul(M + 1, R, l, r, prd);
	len[rt] = len[lch] + len[rch];
}
DB seg_sum(int L, int R, int l, int r) {
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
		return len[rt];
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(dcmp(tag[rt], 1)) {
		len[lch] *= tag[rt];
		len[rch] *= tag[rt];
		tag[lch] *= tag[rt];
		tag[rch] *= tag[rt];
		tag[rt] = 1;
	}
	DB ret = 0;
	if(l <= M)
		ret += seg_sum(L, M, l, r);
	if(M < r)
		ret += seg_sum(M + 1, R, l, r);
	len[rt] = len[lch] + len[rch];
	return ret;
}
Matrix Translation(int dx, int dy, int dz) {
	Matrix ret = {};
	ret.num[1][1] = ret.num[2][2] = ret.num[3][3] = ret.num[4][4] = 1;
	ret.num[4][1] = dx;
	ret.num[4][2] = dy;
	ret.num[4][3] = dz;
	return ret;
}
Matrix Scaling(int cx, int cy, int cz, DB scale) {
	Matrix ret = {};
	ret.num[1][1] = ret.num[2][2] = ret.num[3][3] = scale;
	ret.num[4][1] = (1 - scale) * cx;
	ret.num[4][2] = (1 - scale) * cy;
	ret.num[4][3] = (1 - scale) * cz;
	ret.num[4][4] = 1;
	return ret;
}
Matrix Rotation(int cx, int cy, int cz, int dx, int dy, int dz, DB angle) {
	DB norm2 = sqr(dx) + sqr(dy) + sqr(dz), length = sqrt(norm2);
	DB sinA = sin(angle), cosA = cos(angle);
	Matrix ret = {};
	ret.num[1][1] = dx * dx / norm2 * (1 - cosA) + cosA;
	ret.num[1][2] = dx * dy / norm2 * (1 - cosA) + dz / length * sinA;
	ret.num[1][3] = dx * dz / norm2 * (1 - cosA) - dy / length * sinA;
	ret.num[2][1] = dx * dy / norm2 * (1 - cosA) - dz / length * sinA;
	ret.num[2][2] = dy * dy / norm2 * (1 - cosA) + cosA;
	ret.num[2][3] = dy * dz / norm2 * (1 - cosA) + dx / length * sinA;
	ret.num[3][1] = dx * dz / norm2 * (1 - cosA) + dy / length * sinA;
	ret.num[3][2] = dy * dz / norm2 * (1 - cosA) - dx / length * sinA;
	ret.num[3][3] = dz * dz / norm2 * (1 - cosA) + cosA;
	ret.num[4][4] = 1;
	return Translation(-cx, -cy, -cz) * ret * Translation(cx, cy, cz);
}
void getCoordinates(int id, DB &x, DB &y, DB &z) {
	Matrix &trans = seg_que(1, n, id);
	DB ret[maxs] = {};
	for(int i = 1; i < maxs; ++i)
		for(int j = 1; j < maxs; ++j)
			ret[j] += vec[id][i] * trans.num[i][j];
	x = ret[1];
	y = ret[2];
	z = ret[3];
}
int main() {
	Matrix tmp;
	for(int i = 1; i < maxs; ++i)
		I.num[i][i] = 1;
	for(int Case = 1; scanf("%d%d", &n, &m) == 2 && !(!n && !m); ++Case) {
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j < maxs - 1; ++j)
				scanf("%d", vec[i] + j);
			vec[i][maxs - 1] = 1;
		}
		seg_init(1, n);
		printf("Case #%d:\n", Case);
		while(m--) {
			char op[13];
			scanf("%s", op);
			if(op[0] == 'T') {
				int l, r, x, y, z;
				scanf("%d%d%d%d%d", &l, &r, &x, &y, &z);
				seg_tr(1, n, l, r, tmp = Translation(x, y, z));
				DB x1, y1, z1, x2, y2, z2;
				if(l > 1) {
					getCoordinates(l - 1, x1, y1, z1);
					getCoordinates(l, x2, y2, z2);
					seg_upd(1, n, l - 1, norm(x1 - x2, y1 - y2, z1 - z2));
				}
				if(r < n) {
					getCoordinates(r, x1, y1, z1);
					getCoordinates(r + 1, x2, y2, z2);
					seg_upd(1, n, r, norm(x1 - x2, y1 - y2, z1 - z2));
				}
			} else if(op[0] == 'S') {
				int l, r, x, y, z;
				DB k;
				scanf("%d%d%d%d%d", &l, &r, &x, &y, &z);
				readDB(k);
				seg_tr(1, n, l, r, tmp = Scaling(x, y, z, k));
				DB x1, y1, z1, x2, y2, z2;
				if(l < r)
					seg_mul(1, n, l, r - 1, k);
				if(l > 1) {
					getCoordinates(l - 1, x1, y1, z1);
					getCoordinates(l, x2, y2, z2);
					seg_upd(1, n, l - 1, norm(x1 - x2, y1 - y2, z1 - z2));
				}
				if(r < n) {
					getCoordinates(r, x1, y1, z1);
					getCoordinates(r + 1, x2, y2, z2);
					seg_upd(1, n, r, norm(x1 - x2, y1 - y2, z1 - z2));
				}
			} else if(op[0] == 'R') {
				int l, r, x, y, z, dx, dy, dz;
				DB theta;
				scanf("%d%d%d%d%d%d%d%d", &l, &r, &x, &y, &z, &dx, &dy, &dz);
				readDB(theta);
				seg_tr(1, n, l, r, tmp = Rotation(x, y, z, dx, dy, dz, theta));
				DB x1, y1, z1, x2, y2, z2;
				if(l > 1) {
					getCoordinates(l - 1, x1, y1, z1);
					getCoordinates(l, x2, y2, z2);
					seg_upd(1, n, l - 1, norm(x1 - x2, y1 - y2, z1 - z2));
				}
				if(r < n) {
					getCoordinates(r, x1, y1, z1);
					getCoordinates(r + 1, x2, y2, z2);
					seg_upd(1, n, r, norm(x1 - x2, y1 - y2, z1 - z2));
				}
			} else if(op[0] == 'C') {
				int i;
				scanf("%d", &i);
				DB x, y, z;
				getCoordinates(i, x, y, z);
				writeDB(x, ' ');
				writeDB(y, ' ');
				writeDB(z, '\n');
			} else { // op[0] == 'L'
				int l, r;
				scanf("%d%d", &l, &r);
				writeDB(l < r ? seg_sum(1, n, l, r - 1) : 0, '\n');
			}
		}
	}
	return 0;
}
