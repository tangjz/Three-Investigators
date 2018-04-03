#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()
#define ls t << 1
#define rs t << 1 | 1
#define lss ls, l, mid
#define rss rs, mid + 1, r

const int maxn = 100100;

struct line{
	int x, l, r, v;
	line(){}
	line(int x, int l, int r, int v) : x(x), l(l), r(r), v(v) {}
	bool operator < (const line &R) const{
		return x < R.x;
	}
}l[maxn << 1];

int T, n, m;
int qy[maxn << 1], nn;
int cnt[maxn << 3], tag[maxn << 3];
unsigned sum[maxn << 3];
unsigned base[maxn << 1];

unsigned flag[35][35], f[35][35];
unsigned nim_mult(unsigned x, unsigned y);

inline unsigned Nim_Mult(int x, int y){ //求2^x和2^y的nim积
	if(!x || !y) return 1u << (x + y);
	unsigned &F = f[x][y];
	if(flag[x][y]) return F;
	unsigned ret = 1, e = 1;
	for(int i = 0; i < 6; ++i)
		if (((x ^ y) >> i) & 1) e *= 1u << (1 << i);
		else if ((x >> i) & 1) ret = nim_mult(ret, 3u * (1u << (1 << i)) >> 1);
	F = nim_mult(ret, e);
	flag[x][y] = 1;
	return F;
}

unsigned nim_mult(unsigned x, unsigned y){ //求x和y的nim积
	if(x < 2 || y < 2) return x * y;
	unsigned ret = 0;
	for(int i = 0; i < 32; ++i)
		if((x >> i) & 1)
			for(int j = 0; j < 32; ++j)
				if ((y >> j) & 1)
					ret ^= Nim_Mult(i, j);
	return ret;
}

unsigned g[16][16][8][8];
unsigned F(unsigned x, unsigned y){
	unsigned res = 0;
	for(int i = 0; i < 32; i += 4)
		for(int j = 0; j < 32; j += 4)
			res ^= g[x >> i & 15][y >> j & 15][i >> 2][j >> 2];
	return res;
}

inline int get(int n, int x){
	return ((n >> x + 1) + (n >> x & 1)) & 1;
}

inline int getsum(int l, int r){ // return the lowbit xor sum of [l, r]
	int res = 0;
	for(int i = 0; i < 30; ++i)
		if(get(r, i) ^ get(l - 1, i)) res |= 1 << i;
	return res;
}

void build(int t, int l, int r){
	sum[t] = base[r] ^ base[l - 1];
	cnt[t] = tag[t] = 0;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(lss), build(rss);
}

inline void pushdown(int t){
	cnt[ls] += tag[t];
	cnt[rs] += tag[t];
	tag[ls] += tag[t];
	tag[rs] += tag[t];
	tag[t] = 0;
}

void modify(int t, int l, int r, int x, int y, int v){
	if(x <= l && y >= r){
		cnt[t] += v, tag[t] += v;
		return;
	}
	pushdown(t);
	int mid = (l + r) >> 1;
	if(x <= mid) modify(lss, x, y, v);
	if(y > mid) modify(rss, x, y, v);
	cnt[t] = min(cnt[ls], cnt[rs]);
	sum[t] = 0;
	if(cnt[ls] == cnt[t]) sum[t] ^= sum[ls];
	if(cnt[rs] == cnt[t]) sum[t] ^= sum[rs];
}

int main(){
	freopen("1003.in", "r", stdin);
	freopen("1003.out", "w", stdout);
	for(unsigned i = 0; i < 16; ++i)
		for(unsigned j = 0; j < 16; ++j)
			for(int k = 0; k < 8; ++k)
				for(int l = 0; l < 8; ++l)
					g[i][j][k][l] = nim_mult(i << (4 * k), j << (4 * l));
	scanf("%d", &T);
	while(T--){
		//if(T == 2) break;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; ++i){
			static int x, y, xx, yy;
			scanf("%d%d%d%d", &x, &y, &xx, &yy);
			l[2 * i] = line(x, y, yy + 1, 1);
			l[2 * i + 1] = line(xx + 1, y, yy + 1, -1);
			qy[2 * i] = y;
			qy[2 * i + 1] = yy + 1;
		}
		sort(qy, qy + 2 * m);
		nn = unique(qy, qy + 2 * m) - qy - 1;
		for(int i = 0; i < nn; ++i)
			base[i + 1] = getsum(qy[i], qy[i + 1] - 1) ^ base[i];
		
		sort(l, l + 2 * m);
		build(1, 1, nn);
		unsigned res = 0;
		for(int i = 0, j = 0; i < 2 * m; i = j){
			while(j < 2 * m && l[j].x == l[i].x){
				l[j].l = lower_bound(qy, qy + nn, l[j].l) - qy + 1;
				l[j].r = lower_bound(qy, qy + nn, l[j].r) - qy + 1;
				modify(1, 1, nn, l[j].l, l[j].r - 1, l[j].v);
				++j;
			}
			if(j == 2 * m) break;
			unsigned tmp = getsum(l[i].x, l[j].x - 1);
			unsigned tmp2 = base[nn] ^ (cnt[1] ? 0 : sum[1]);
			res ^= F(tmp, tmp2);
		}
		printf("%s\n", res ? "Yong Chol" : "Brother");
	}
	return 0;
}
