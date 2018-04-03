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

int n, m, k;
bitset<100> b[18];
int bb[105];
int C[105][105];
int ans;
int cnt[1 << 18], cnt2[1 << 18];

int main(){
	scanf("%d%d%d", &n, &m, &k);
	
	for(int i = 0; i <= n; C[i++][0] = 1)
		for(int j = 1; j <= i; ++j)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % M;

	for(int i = 0, k, x; i < m; ++i){
		scanf("%d", &k);
		while(k--){
			scanf("%d", &x);
			b[i].set(x - 1);
		}
	}
	
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			bb[i] |= b[j][i] << j;

	int all = (1 << m) - 1;
	for(int mask = 1; mask < 1 << m; ++mask){
		for(int i = 0; i < n; ++i)
			cnt[bb[i] & mask] = cnt2[bb[i] & mask] = cnt2[(all ^ bb[i]) & mask] = 0;

		for(int i = 0; i < n; ++i)
			++cnt[bb[i] & mask], ++cnt2[bb[i] & mask];

		int tmp = 0;
		for(int i = 0; i < n; ++i){
			tmp = (tmp + (ll)C[cnt[bb[i] & mask]][k] * C[cnt2[(all ^ bb[i]) & mask]][k]) % M;
			cnt[bb[i] & mask] = 0;
			cnt2[(all ^ bb[i]) & mask] = 0;
		}
		
		//printf("%d %d\n", mask, tmp);
		
		if(__builtin_popcount(mask) & 1) ans = (ans + tmp) % M;
		else ans = (ans + M - tmp) % M;
	}

	printf("%d\n", ans);
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
