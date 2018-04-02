#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T;
int n, k;
int a[100100];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; ++i) scanf("%d", a + i);
		sort(a + 1, a + n + 1);
		int ans = 0;
		for(int i = n; i >= 1; --i){
			ans++;
			if(i > 1 && a[i] - a[i - 1] > k) break;
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
