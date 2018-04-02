#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int main(){
	ll k, m;
	while(~scanf("%lld%lld", &m, &k)){
		printf("%lld\n", k + (m - k) * k);
	}
	return 0;
}
