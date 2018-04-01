#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define pii pair<int, int>
#define M 1000000007
#define all(a) a.begin(), a.end()

int n, m;
int x[100005], y[100005], w[100005];
int U[200005], D[200005], tag[200005];

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i){
		scanf("%d%d", x + i, y + i);
		w[i] = i;
	}
	sort(w + 1, w + m + 1, [](int i, int j) { return x[i] > x[j]; });

	for(int i = 1; i <= m; ++i){
		int x = w[i];
		U[y[x] + 1] = U[y[x]] + 1;
		D[y[x]] = D[y[x] + 1] + 1;
	}
	for(int i = 1; i <= n; ++i){
		++tag[i - U[i]];
		--tag[i + D[i] + 1];
		//printf("%d %d\n", U[i], D[i]);
	}
	for(int i = 1, now = 0; i <= n; ++i){
		now += tag[i];
		printf("%d ", now);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
