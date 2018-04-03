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

int n;
ll s;
__int128 cnt[60][2];
__int128 MX[60], MI[60];

void dfs(int dp, __int128 k, ll a){
	if(dp == -1){
		if(k == s){
			printf("%lld\n", a);
#ifndef ONLINE_JUDGE
			system("pause");
#endif
			exit(0);
		}
		return;
	}
	if(k + MI[dp] > s || k + MX[dp] < s) return;

	dfs(dp - 1, k + (cnt[dp][1] << dp), a);
	if(cnt[dp][1] != cnt[dp][0]) dfs(dp - 1, k + (cnt[dp][0] << dp), a + (1LL << dp));
}

int main(){
	scanf("%d%lld", &n, &s);
	for(int i = 1; i <= n; ++i){
		static ll x;
		scanf("%lld", &x);
		for(int j = 0; j <= 59; ++j)
			++cnt[j][x >> j & 1];
	}

	MX[0] = max(cnt[0][0], cnt[0][1]);
	MI[0] = min(cnt[0][0], cnt[0][1]);
	for(int j = 1; j <= 59; ++j){
		MX[j] = MX[j - 1] + (max(cnt[j][0], cnt[j][1]) << j);
		MI[j] = MI[j - 1] + (min(cnt[j][0], cnt[j][1]) << j);
	}
	
	dfs(59, 0, 0);
	printf("-1");
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
