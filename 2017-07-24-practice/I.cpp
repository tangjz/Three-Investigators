#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()
#define FOR(i,l,r) for(int i = l; i <= r; ++i)
#define ROF(i,r,l) for(int i = r; i >= l; --i)
#define ls (t << 1)
#define rs ((t << 1) | 1)
#define mid ((l + r) >> 1)

const int maxn = 100100;
int n, T;
int Log[maxn];
char str[maxn];
int tr[2][maxn * 4];
struct SA{
	int c[maxn], t1[maxn], sa[maxn], t2[maxn], height[maxn], ran[maxn];
	int lcp[maxn][20];

	void init(){
		int i,*x=t1,*y=t2,m=300;
		for(int i = 1; i <= m; ++i) c[i] = 0; c[0]=1;
		FOR(i,1,n) c[x[i]=str[i]]++;
		FOR(i,1,m) c[i]+=c[i-1];
		ROF(i,n,1) sa[--c[x[i]]]=i;
		for(int k=1;k<=n;k<<=1){
			int p=1;
			FOR(i,n-k+1,n) y[p++]=i;
			FOR(i,1,n) if (sa[i]>k) y[p++]=sa[i]-k;
			for(int i = 1; i <= m; ++i) c[i] = 0; c[0]=1; 
			FOR(i,1,n) c[x[y[i]]]++;
			FOR(i,1,m) c[i]+=c[i-1];
			ROF(i,n,1) sa[--c[x[y[i]]]]=y[i];

			swap(x,y);
			p=2; x[sa[1]]=1;
			for(i=2;i<=n;i++)
				x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
			if (p>n) break; m=p;
		}
		FOR(i,1,n) ran[sa[i]]=i;
		int k=0;
		for(int i=1;i<=n;i++){
			if(k)k--;int j=sa[ran[i]-1];
			while(str[i+k]==str[j+k])k++;
			height[ran[i]]=k;
		}
	}
	void build_rmq(){
		for(int i = 1; i <= n; ++i) lcp[i][0] = height[i];
		for(int j = 1; j < 17; ++j)
			for(int i = (1 << j - 1) + 1; i <= n; ++i)
				lcp[i][j] = min(lcp[i][j - 1], lcp[i - (1 << j - 1)][j - 1]);
	}
	inline int get_lcp(int x, int y){
		if(x > y) swap(x, y);
		int k = Log[y - x];
		return min(lcp[y][k], lcp[x + (1 << k)][k]);
	}
}T1, T2;

void ban(int k, int t, int l, int r, int x){
	tr[k][t]--;
	if(l == r) return;
	if(x <= mid) ban(k, ls, l, mid, x);
	else ban(k, rs, mid + 1, r, x);
}

void build(int t, int l, int r){
	tr[0][t] = tr[1][t] = r - l + 1;
	if(l == r) return;
	build(ls, l, mid), build(rs, mid + 1, r);
}

int get_nex(int k, int t, int l, int r, int x, int y){
	if(!tr[k][t]) return -1;
	if(l == r) return l;
	int res = -1;
	if(x > mid || (res = get_nex(k, ls, l, mid, x, y)) == -1)
		if(y > mid) res = get_nex(k, rs, mid + 1, r, x, y);
	return res;
}

int ask(int k, int t, int l, int r, int x, int y){
	if(x <= l && y >= r) return tr[k][t];
	return (x <= mid ? ask(k, ls, l, mid, x, y) : 0) + 
		(y > mid ? ask(k, rs, mid + 1, r, x, y) : 0);
}

int main(){
	scanf("%d", &T);
	for(int i = 0; i <= 16; ++i) Log[1 << i] = i;
	for(int i = 1; i <= 100000; ++i)
		Log[i] = max(Log[i], Log[i - 1]);
	while(T--){
		scanf("%s", str + 1);
		n = strlen(str + 1);
		T1.init(); T1.build_rmq();
		reverse(str + 1, str + n + 1);
		T2.init(); T2.build_rmq();
		
		ll ans = (ll)n * (n + 1) / 2;
		build(1, 1, n);

		for(int len = 1; len * 2 <= n; ++len){
			for(int i = len + 1; i + len - 1 <= n; i += len){
				int suf = T2.get_lcp(T2.ran[n - i + 2], T2.ran[n - i + 2 - len]);
				int pre = i + len <= n ? T1.get_lcp(T1.ran[i], T1.ran[i + len]) : 0;
				pre = min(pre, len - 1), suf = min(suf, len);
				
				if(pre + suf - len >= 0){
					int l1 = i - suf, r1 = i + pre - len;
					int l2 = i + 2 * len - suf - 1, r2 = i + len + pre - 1;
					int t;
					while(t = get_nex(0, 1, 1, n, l1, r1), t != -1){
						ans -= ask(1, 1, 1, n, t + 2 * len - 1, n);
						ban(0, 1, 1, n, t);
					}
					while(t = get_nex(1, 1, 1, n, l2, r2), t != -1){
						ans -= ask(0, 1, 1, n, 1, t - 2 * len + 1);
						ban(1, 1, 1, n, t);
					}
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
