#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

bool check(int k, ll n){
	double kk = pow(k, k);
	if(kk - 10 <= n){
		ll res = 1;
		for(int i = 1; i <= k; ++i)
			res = res * k;
		return res <= n;
	}else return 0;
}

int main(){
	ll n;
	while(~scanf("%lld", &n)){
		int k = 1;
		while(check(k, n)) ++k;
		printf("%d\n", k - 1);
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
