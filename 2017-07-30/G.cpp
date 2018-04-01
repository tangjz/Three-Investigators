#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()
#define ls (t << 1)
#define rs ((t << 1) | 1)

const int maxn = 802;
int tmin[maxn << 2][maxn << 2];
int tmax[maxn << 2][maxn << 2];
int a[maxn][maxn];
int n, q, A, B;

void modify(int t1, int t, int l, int r, bool tag, int x, int y){
	if(l == r){
		if(tag){
			tmin[t1][t] = tmax[t1][t] = a[x][y];
		}else{
			tmin[t1][t] = min(tmin[t1 << 1][t], tmin[(t1 << 1) | 1][t]);
			tmax[t1][t] = max(tmax[t1 << 1][t], tmax[(t1 << 1) | 1][t]);
		}
		return;
	}
	int mid = (l + r) >> 1;
	if(y <= mid) modify(t1, ls, l, mid, tag, x, y);
	else modify(t1, rs, mid + 1, r, tag, x, y);
	tmin[t1][t] = min(tmin[t1][ls], tmin[t1][rs]);
	tmax[t1][t] = max(tmax[t1][ls], tmax[t1][rs]);
}

void modify(int t, int l, int r, int x, int y){
	if(l == r) return (void)modify(t, 1, 1, n, 1, x, y);
	int mid = (l + r) >> 1;
	if(x <= mid) modify(ls, l, mid, x, y);
	else modify(rs, mid + 1, r, x, y);
	modify(t, 1, 1, n, 0, x, y);
}

void ask(int t1, int t, int l, int r, int x, int y){
	if(x <= l && y >= r){
		A = min(A, tmin[t1][t]);
		B = max(B, tmax[t1][t]);
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) ask(t1, ls, l, mid, x, y);
	if(y > mid) ask(t1, rs, mid + 1, r, x, y);
}

void ask(int t, int l, int r, int x, int y, int xx, int yy){
	if(x <= l && y >= r){
		ask(t, 1, 1, n, xx, yy);
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) ask(ls, l, mid, x, y, xx, yy);
	if(y > mid) ask(rs, mid + 1, r, x, y, xx, yy);
}

int main(){
	int T, ca = 0;
	scanf("%d", &T);
	while(T--){
		printf("Case #%d:\n", ++ca);
		scanf("%d", &n);
		memset(tmin, 127, sizeof(tmin));
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j){
				scanf("%d", a[i] + j);
				modify(1, 1, n, i, j);
			}
		scanf("%d", &q);
		while(q--){
			static int x, y, L;
			scanf("%d%d%d", &x, &y, &L);
			A = M, B = 0;
			int l1 = max(x - L / 2, 1), r1 = min(x + L / 2, n);
			int l2 = max(y - L / 2, 1), r2 = min(y + L / 2, n);
			ask(1, 1, n, l1, r1, l2, r2);
			a[x][y] = (A + B) / 2;
			modify(1, 1, n, x, y);
			printf("%d\n", a[x][y]);
		}
	}
	
	return 0;
}
