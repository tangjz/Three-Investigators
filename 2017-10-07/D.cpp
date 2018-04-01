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

const ll inf = 1LL << 60;
int n, r, p;
ll f[1000005];

ll work(int i){
	if(f[i] != -1) return f[i];
	f[i] = inf;
	for(int j = 1, k; j < i; j = k){
		int x = (i + j) / (j + 1);
		if(x > 1){
			k = (i - 1) / (x - 1);
		}else k = j + 1;
			
		ll tmp = work(x) + r + (ll)p * j;
		if(tmp < f[i]) f[i] = tmp;
	}
	return f[i];
}

int main(){
	scanf("%d%d%d", &n, &r, &p);
	
	memset(f, -1, sizeof(f));
	f[1] = 0;
	work(n);
	
	printf("%lld\n", f[n]);
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
