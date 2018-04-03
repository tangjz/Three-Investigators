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
int x[100005], r[100005];

int main(){
	scanf("%d", &n);
	int mx = 0;
	for(int i = 1; i <= n; ++i){
		scanf("%d%d", x + i, r + i);
		if(i > 1){
			if(mx < x[i]){
				printf("-1\n");
				return 0;
			}
		}
		mx = max(mx, x[i] + r[i]);
	}
	
	int mi = 1 << 30;
	for(int i = n; i >= 1; --i){
		if(i < n){
			if(mi > x[i]){
				printf("-1\n");
				return 0;
			}
		}
		mi = min(mi, x[i] - r[i]);
	}
	
	ll ans = 3LL * (x[n] - x[1]);
	printf("%lld\n", ans);
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
