#include<bits/stdc++.h>
using namespace std;
#define ls t << 1
#define rs t << 1 | 1
#define lss ls, l, mid
#define rss rs, mid + 1, r

const int maxn = 100100;
const int inf = 1e9;

int n;
int a[maxn];
int sta[maxn];
int pre[maxn], nex[maxn];
int t0[maxn << 2], t1[maxn << 2];
bool des[maxn];

void build(int t, int l, int r){
	if(l == r){
		t0[t] = a[l] - l;
		t1[t] = a[l] + l;
		return;	
	}
	int mid = (l + r) >> 1;
	build(lss), build(rss);
	t0[t] = min(t0[ls], t0[rs]);
	t1[t] = min(t1[ls], t1[rs]);
}

void modify(int t, int l, int r, int x){
	if(l == r){
		t0[t] = -inf;
		t1[t] = -inf;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) modify(lss, x);
	else modify(rss, x);
	t0[t] = min(t0[ls], t0[rs]);
	t1[t] = min(t1[ls], t1[rs]);
}

int ask0(int t, int l, int r, int y, int lim){
	if(t0[t] > lim) return -1;
	if(l == r) return l;
	int mid = (l + r) >> 1;
	int tmp = y > mid ? ask0(rss, y, lim) : -1;
	return tmp == -1 ? ask0(lss, y, lim) : tmp;
}

int ask1(int t, int l, int r, int y, int lim){
	if(t1[t] > lim) return -1;
	if(l == r) return l;
	int mid = (l + r) >> 1;
	int tmp = y <= mid ? ask1(lss, y, lim) : -1;
	return tmp == -1 ? ask1(rss, y, lim) : tmp;
}

int lef(int x){
	int res = 0, lim = a[x] - x;
	while(x > 1){
		int y = ask0(1, 1, n, x - 1, lim);
		if(y == -1 || des[y]) return res;
		des[y] = 1;
		++res;
		modify(1, 1, n, y);
		x = y;
	}
	return res;
}

int rig(int x){
	int res = 0, lim = a[x] + x;
	while(x < n){
		int y = ask1(1, 1, n, x + 1, lim);
		if(y == -1 || des[y]) return res;
		des[y] = 1;
		++res;
		modify(1, 1, n, y);
		x = y;
	}
	return res;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", a + i);
	build(1, 1, n);
	int m, x; scanf("%d", &m);
	while(m--){
		scanf("%d", &x);
		des[x] = 1;
		modify(1, 1, n, x);
		int ans = lef(x) + rig(x) + 1;
		printf("%d\n", ans);
	}
	return 0;
}
