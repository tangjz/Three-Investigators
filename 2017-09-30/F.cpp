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

const int maxn = 100005;
int n, k, p;
int a[maxn];

int main(){
	scanf("%d%d%d", &n, &k, &p);
	ll ans = n - k;
	int last = n - k, now = 2;
	for(int i = 1; i <= n - k; ++i) a[i] = 1;
	for(int i = n - k + 1; i <= n; ++i){
		if(100 * last >= p * (i - 1)) ans += now;
		else{
			last = i - 1;
			ans += ++now;
		}
		a[i] = now;
	}
	printf("%I64d\n", ans);
	for(int i = 1; i <= n; ++i)
		printf("%d%c", a[i], " \n"[i == n]);
	return 0;
}
