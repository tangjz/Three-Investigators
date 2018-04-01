#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, n, a[60];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		double ans = 0;
		double base = 1;
		for(int i = 1; i <= n; ++i){
			scanf("%d", a + i);
		}
		sort(a + 1, a + n + 1);
		reverse(a + 1, a + n + 1);
		for(int i = 1; i <= n; ++i){
			ans += base * a[i];
			base *= 0.95;
		}
			
		printf("%.10f\n", ans);
	}
	return 0;
}
