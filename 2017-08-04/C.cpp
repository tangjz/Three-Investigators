#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, s, n;
int v[60], c[60];
ll f[6000];

int main(){
	int ca = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &s, &n);
		for(int i = 1; i <= n; ++i) scanf("%d%d", v + i, c + i);
		ll ans = 0;
		for(int i = 1; i <= s; ++i)
			if(s % i == 0){
				memset(f, 0, sizeof(ll) * (s / i + 1));
				f[0] = 1;
				for(int j = 1; j <= n; ++j)
					if(c[j] >= i)
						for(int k = s / i; k >= v[j]; --k)
							f[k] += f[k - v[j]];
				ans += f[s / i];
			}
		printf("Case %d: %lld\n", ++ca, ans);
	}
	
	return 0;
}
