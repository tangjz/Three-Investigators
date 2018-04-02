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

const int inf = 1e9;
const int maxn = 305;
int n, m, P;
int a[maxn][maxn];
int b[maxn];
int s[maxn];
int L[maxn];
int R[maxn];
int mi[maxn];

int main(){
	while(~scanf("%d%d%d", &n, &m, &P)){
		int ans = -inf, mii = inf, sum = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j){				
				scanf("%d", a[i] + j);
				mii = min(mii, a[i][j]);
				sum += a[i][j];
			}
		ans = sum - mii + P;

		for(int i = 1; i <= n; ++i){
			for(int k = 1; k <= m; ++k) mi[k] = inf, b[k] = 0;
			for(int j = i; j <= n; ++j){
				for(int k = 1; k <= m; ++k){
					mi[k] = min(mi[k], a[j][k]);
					b[k] = b[k] + a[j][k];
				}
				
				int now = 0;
				for(int k = 1; k <= m; ++k){
					s[k] = s[k - 1] + b[k];
					if(!(i == 1 && j == n && k == m))
						ans = max(ans, s[k] - now);
					now = min(now, s[k]);
					L[k] = s[k] - now;
				}
				
				s[m + 1] = R[m + 1] = 0;
				now = 0;
				for(int k = m; k >= 1; --k){
					s[k] = s[k + 1] + b[k];
					if(!(i == 1 && j == n && k == 1))
						ans = max(ans, s[k] - now);
					now = min(now, s[k]);
					R[k] = s[k] - now;
					ans = max(ans, L[k - 1] + R[k + 1] + b[k] + P - mi[k]);
				}
			}
		}
		
		printf("%d\n", ans);
	}
	return 0;
}
