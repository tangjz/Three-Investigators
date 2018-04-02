#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int cnt[1000100];
int dp[1000100][3][2];

inline void ckmax(int &a, int b){
	(a < b) && (a = b);
}

int main(){
	int n;
	while(~scanf("%d", &n)){
		memset(cnt, 0, sizeof(int) * (n + 1));
		for(int i = 1, x; i <= n; ++i){
			scanf("%d", &x);
			++cnt[x];
		}
		memset(dp[0], 128, sizeof(dp[0]));
		dp[0][0][0] = 0;
		for(int i = 1; i <= n; ++i){
			memset(dp[i], 128, sizeof(dp[i]));
			for(int j = 0; j <= 2; ++j)
				for(int k = 0; k <= 1; ++k)
					for(int jj = 0; jj <= 2 && jj <= cnt[i]; ++jj){
						ckmax(dp[i][jj][min(j, 1)], dp[i - 1][j][k] + (cnt[i] - jj) / 2);
						if(k && j && (cnt[i] - jj)) ckmax(dp[i][jj][j - 1], dp[i - 1][j][k] + (cnt[i] - jj - 1) / 2 + 1);
					}
		}
		int res = 0;
		for(int i = 0; i <= 2; ++i)
			for(int j = 0; j <= 1; ++j)
				ckmax(res, dp[n][i][j]);
		printf("%d\n", res);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
