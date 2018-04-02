#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int n, m;
int fa[100100];
int w[200100], u[200100], v[200100], p[200100];

int find(int x){
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int main(){
	while(~scanf("%d%d", &n, &m)){
		for(int i = 1; i <= n; ++i){
			static int x, y;
			scanf("%d%d", &x, &y);
		}
		int sum = 0;
		for(int i = 1; i <= m; ++i){
			scanf("%d%d%d", u + i, v + i, w + i);
			sum += w[i];
			p[i] = i;
		}
		int cnt = m;
		sort(p + 1, p + m + 1, [](int i, int j) { return w[i] > w[j]; });
		for(int i = 1; i <= n; ++i) fa[i] = i;
		for(int i = 1; i <= m; ++i){
			int x = find(u[p[i]]), y = find(v[p[i]]);
			if(x != y){
				--cnt;
				sum -= w[p[i]];
				fa[x] = y;
			}
		}
		printf("%d %d\n", cnt, sum);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
