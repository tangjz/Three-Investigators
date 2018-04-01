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

int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	if(n > k){
		printf("%d\n", k);
	}else{
		int t = k / (n - 1), r = k % (n - 1);
		int ans = (n - 1 - r) * t * (t - 1) + r * t * (t + 1);
		printf("%d\n", ans + k);
	}
	

	return 0;
}
