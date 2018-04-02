#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

const int maxn = 100100;
int T, n, m;
int fa[maxn];
int cnt[2];
int u[maxn], v[maxn], w[maxn];
int f[1000];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

bool merge(int x, int y){
	x = find(x), y = find(y);
	if(x == y) return 0;
	fa[x] = y; return 1;
}

int work(bool k){
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1; i <= m; ++i)
		if(w[i] == k) merge(u[i], v[i]);
	int cnt = 0;
	for(int i = 1; i <= n; ++i)
		cnt += find(i) == i;
	return cnt - 1;
}

int main(){
	int ca = 0;
	scanf("%d", &T);
	f[0] = f[1] = 1;
	for(int i = 2; f[i - 1] < 100000; ++i)
		f[i] = f[i - 1] + f[i - 2];
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) fa[i] = i;
		cnt[0] = cnt[1] = 0;
		for(int i = 1; i <= m; ++i){
			scanf("%d%d%d", u + i, v + i, w + i);
			merge(u[i], v[i]);
			cnt[w[i]]++;
		}
		bool flag = 1;
		for(int i = 2; i <= n; ++i)
			flag &= find(i) == find(1);
		printf("Case #%d: ", ++ca);
		if(!flag) printf("No\n");
		else{
			int need_b = work(1), need_w = work(0);
			int res = n - 1 - need_b - need_w;
			int L = need_w, R = min(need_w + res, cnt[1]);
			int i; for(i = 1; f[i] < L; ++i);
			if(f[i] <= R) printf("Yes\n");
			else printf("No\n");
		}
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
