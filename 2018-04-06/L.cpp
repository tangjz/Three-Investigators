#include<bits/stdc++.h>
using namespace std;
#define ll long long

int n, m, ca;
ll a[100005], b[100005];

bool work(){
	while(1){
		if(a[n] > b[m]){
			if(n > 1 && a[n] + a[n - 1] > b[m] + b[m - 1]) a[n - 1] += a[n], --n;
			else --m;
		}else{
			if(n == 1) return 0;
			else a[n - 1] += a[n], --n;
		}
		if(!m) return 1;

		if(b[m] > a[n]){
			if(m > 1 && b[m] + b[m - 1] > a[n] + a[n - 1]) b[m - 1] += b[m], --m;
			else --n;
		}else{
			if(m == 1) return 1;
			else b[m - 1] += b[m], --m;
		}
		if(!n) return 0;
	}
}

int main(){
	while(~scanf("%d%d", &n, &m)){
		for(int i = 1; i <= n; ++i)
			scanf("%I64d", a + i);
		for(int i = 1; i <= m; ++i)
			scanf("%I64d", b + i);
		sort(a + 1, a + n + 1);
		sort(b + 1, b + m + 1);
		printf("Case %d: %s\n", ++ca, work() ? "Takeover Incorporated" : "Buyout Limited");
	}
	return 0;
}
