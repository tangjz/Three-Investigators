#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, n, m;
ll b[10010], s[10010];
int a[60];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 0; i <= m; ++i) scanf("%lld", b + i);
		int k = 0;
		while((1 << k) < b[0]) ++k;
		for(int i = 0; i <= m; ++i) b[i] /= (1 << k);
		for(int i = 1; i <= k; ++i) a[i] = 0;
		
		int ts = 0;
		memset(s, 0, sizeof(s));
		s[0] = 1;
		for(int i = 1; i <= m; ++i)
			if(b[i]){
				int t = b[i];
				for(int j = 1; j <= t; ++j){
					a[++k] = i;
					for(int k = ts; k >= 0; --k){
						b[k + i] -= s[k];
						s[k + i] += s[k];
					}
					ts += i;
				}
			}
		for(int i = 1; i <= n; ++i) printf("%d%c", a[i], " \n"[i == n]);
	}
	return 0;
}
