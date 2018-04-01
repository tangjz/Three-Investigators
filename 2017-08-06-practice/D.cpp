#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, n;
int a[2010], f[1010], ff[1010];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		int sum = 0;
		for(int i = 1; i <= n; ++i){
			scanf("%d", a + i);			
			sum += a[i];
		}
		sum >>= 1;
		memset(f, 0, sizeof(f));
		f[0] = 1;
		for(int i = 1; i <= n; ++i){
			memcpy(ff, f, sizeof(f));
			memset(f, 0, sizeof(f));				
			for(int j = 0; j <= a[i]; ++j){
				for(int k = 0; k + j <= sum; ++k)
					(f[k + j] += ff[k]) %= M;
			}
		}
		printf("%d\n", f[sum]);
	}
	return 0;
}
