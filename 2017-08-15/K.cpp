#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, x;
int a[10001000];

int main(){
	scanf("%d", &T);
	a[1] = 1, a[2] = a[3] = 2;
	int now = 2;
	for(int i = 3, j = 4; j <= 10000000; ++i){
		now = 3 - now;
		for(int k = j; k - j < a[i]; ++k)
			a[k] = now;
		j += a[i];
	}
	
	while(T--){
		scanf("%d", &x);
		printf("%d\n", a[x]);
	}
	
	return 0;
}
