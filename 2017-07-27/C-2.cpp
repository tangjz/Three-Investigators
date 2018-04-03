#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 998244353
#define all(a) a.begin(), a.end()

int T, n, m;
char mp[1010];
bool ban_h[1010][2], ban_c[1010][2];

int main(){
	freopen("1003.in", "r", stdin);
	freopen("1003.out", "w", stdout);
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		memset(ban_h, 0, sizeof(ban_h));
		memset(ban_c, 0, sizeof(ban_c));
		for(int i = 0; i < n; ++i){
			scanf("%s", mp);
			for(int j = 0; j < m; ++j)
				if(mp[j] != '?'){
					bool x = mp[j] == 'R' ? 0 : 1;
					ban_h[i][j & 1 ^ x] = 1;
					ban_c[j][i & 1 ^ x] = 1;
				}
		}
		int res1 = 1, res1_0 = 1, res1_1 = 1;
		for(int i = 0; i < n; ++i){
			res1 = (res1 * (!ban_h[i][0] + !ban_h[i][1])) % M;
			res1_0 *= !ban_h[i][i & 1];
			res1_1 *= !ban_h[i][i & 1 ^ 1];
		}
		int res2 = 1, res2_0 = 1, res2_1 = 1;
		for(int i = 0; i < m; ++i){
			res2 = (res2 * (!ban_c[i][0] + !ban_c[i][1])) % M;
			res2_0 *= !ban_c[i][i & 1];
			res2_1 *= !ban_c[i][i & 1 ^ 1];
		}
		int ans = (res1 + res2 - res1_0 * res2_0 - res1_1 * res2_1) % M;
		if(ans < 0) ans += M;
		printf("%d\n", ans);
	}
	return 0;
}
