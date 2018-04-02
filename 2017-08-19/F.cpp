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
#define lss ls, l, mid
#define rss rs, mid + 1, r

int T, n, q;
int last[400100][2][2], cnt[400100][2];
int cal[2], R[2][2], _cal[2], _R[2][2];
char s[100100];
bool tag[400100];

inline void merge(int L[][2], int p[][2], int q[][2]){
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 2; ++j)
			for(int k = 0; k < 2; ++k)
				L[i][k] = (L[i][k] + (ll)q[i][j] * p[j][k]) % M;
}

void build(int t, int l, int r){
	memset(last[t], 0, sizeof(last[t]));
	tag[t] = 0;
	if(l == r){
		bool x = s[l] - '0';

		last[t][x][x] = 1;
		last[t][x][x ^ 1] = 0;
		
		last[t][x ^ 1][0] = last[t][x ^ 1][1] = 1;
		
		cnt[t][x] = 1;
		cnt[t][x ^ 1] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(lss);
	build(rss);
	
	merge(last[t], last[ls], last[rs]);
	cnt[t][0] = (cnt[ls][0] + (ll)cnt[rs][0] * last[ls][0][0] + (ll)cnt[rs][1] * last[ls][1][0]) % M;
	cnt[t][1] = (cnt[ls][1] + (ll)cnt[rs][0] * last[ls][0][1] + (ll)cnt[rs][1] * last[ls][1][1]) % M;
}

void down(int t){
	tag[ls] ^= 1, tag[rs] ^= 1;
	swap(last[ls][0][0], last[ls][1][0]);
	swap(last[ls][0][1], last[ls][1][1]);
	swap(last[ls][0][0], last[ls][0][1]);
	swap(last[ls][1][0], last[ls][1][1]);

	swap(cnt[ls][0], cnt[ls][1]);
	swap(last[rs][0][0], last[rs][1][0]);
	swap(last[rs][0][1], last[rs][1][1]);
	swap(last[rs][0][0], last[rs][0][1]);
	swap(last[rs][1][0], last[rs][1][1]);
	swap(cnt[rs][0], cnt[rs][1]);
	tag[t] = 0;
}

void modify(int t, int l, int r, int x, int y){
	if(x <= l && y >= r){
		tag[t] ^= 1;
		swap(last[t][0][0], last[t][1][0]);
		swap(last[t][0][1], last[t][1][1]);
		swap(last[t][0][0], last[t][0][1]);
		swap(last[t][1][0], last[t][1][1]);
		swap(cnt[t][0], cnt[t][1]);
		return;
	}
	if(tag[t]) down(t);
	int mid = (l + r) >> 1;
	if(x <= mid) modify(lss, x, y);
	if(y > mid) modify(rss, x, y);
	memset(last[t], 0, sizeof(last[t]));
	merge(last[t], last[ls], last[rs]);
	cnt[t][0] = (cnt[ls][0] + (ll)cnt[rs][0] * last[ls][0][0] + (ll)cnt[rs][1] * last[ls][1][0]) % M;
	cnt[t][1] = (cnt[ls][1] + (ll)cnt[rs][0] * last[ls][0][1] + (ll)cnt[rs][1] * last[ls][1][1]) % M;
}

void query(int t, int l, int r, int x, int y){
	if(x <= l && y >= r){
		memcpy(_cal, cal, sizeof(cal));
		memcpy(_R, R, sizeof(R));
		memset(R, 0, sizeof(R));
		merge(R, _R, last[t]);
		cal[0] = (_cal[0] + (ll)cnt[t][0] * _R[0][0] + (ll)cnt[t][1] * _R[1][0]) % M;
		cal[1] = (_cal[1] + (ll)cnt[t][0] * _R[0][1] + (ll)cnt[t][1] * _R[1][1]) % M;
		return;
	}
	if(tag[t]) down(t);
	int mid = (l + r) >> 1;
	if(x <= mid) query(lss, x, y);
	if(y > mid) query(rss, x, y);
}

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &q);
		scanf("%s", s + 1);
		build(1, 1, n);
		while(q--){
			static int ty, l, r;
			scanf("%d%d%d", &ty, &l ,&r);
			if(ty == 1) modify(1, 1, n, l, r);
			else{
				memset(cal, 0, sizeof(cal));
				memset(R, 0, sizeof(R));
				R[0][0] = 1, R[1][1] = 1;
				query(1, 1, n, l, r);
				printf("%d\n", (cal[0] + cal[1]) % M);
			}
		}
	}
	return 0;
}D
