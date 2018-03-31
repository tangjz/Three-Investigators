#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int Test = 2000000;
char s[55];
ll a[50];
ll C[55][55];
int n, k, m;

ll randll(){
	ll res = 0;
	for(int i = 0; i < 4; ++i)
		res = res << 15 | (rand() & ((1 << 15) - 1));
	return res;
}

int main(){
	freopen("close.in", "r", stdin);
	freopen("close.out", "w", stdout);
	scanf("%d%d%d", &n, &k, &m);
	for(int i = 0; i < k; ++i){
		scanf("%s", s);
		for(int j = 0; j < n; ++j)
			if(s[j] - '0') a[i] |= 1LL << j;
	}
	for(int i = 0; i <= n; C[i++][0] = 1)
		for(int j = 1; j <= i; ++j)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	
	ll tot = 0;
	for(int i = 0; i < m; ++i)
		tot += C[n][i];
	
	double cnt = 0;
	for(int test = 0; test < Test; ++test){
		int p = rand() % k;
		ll r = randll() % tot;
		int x = 0; while(r - C[n][x] >= 0) r -= C[n][x++];
		ll num = 0;
		for(int i = 0; i < n; ++i){
			bool t = a[p] >> i & 1;
			if(x && r >= C[n - 1 - i][x]){
				r -= C[n - 1 - i][x--];
				t ^= 1;
			}
			num |= (ll)t << i;
		}
		int f = 0;
		for(int i = 0; i < k; ++i)
			if(__builtin_popcountll(num ^ a[i]) < m) ++f;
		cnt += 1. / f;
	}
	printf("%f\n", cnt * tot * k / Test);
	
	return 0;
}
