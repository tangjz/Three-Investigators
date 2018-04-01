#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll n;
int a[100];
ll f[30][2][2];

ll work(ll n){
	if(n == 0) return 1;
	int len = 0;
	while(n){
		a[++len] = n % 5;
		n /= 5;
	}
	if(len == 1) return a[1];
	memset(f, 0, sizeof(f));	
	for(int i = 0; i < a[len]; ++i) ++f[len][0][i & 1 & (~len & 1)];
	f[len][1][a[len] & 1 & (~len & 1)] = 1;
	for(int i = len - 1; i; --i){
		if(~i & 1){
			for(int j = 0; j < 5; ++j){
				for(int k = 0; k < 2; ++k){
					f[i][0][k ^ (j & 1)] += f[i + 1][0][k];
					if(j < a[i]) f[i][0][k ^ (j & 1)] += f[i + 1][1][k];
				if(j == a[i]) f[i][1][k ^ (j & 1)] += f[i + 1][1][k];
				}
			}
		}else{
			for(int j = 0; j < 5; ++j){
				for(int k = 0; k < 2; ++k){
					f[i][0][k] += f[i + 1][0][k];
					if(j < a[i]) f[i][0][k] += f[i + 1][1][k];
				if(j == a[i]) f[i][1][k] += f[i + 1][1][k];
				}
			}
		}
	}
	return f[1][0][0];
}

int main(){
	while(scanf("%lld", &n), n != -1){
		printf("%lld\n", work(n + 1));
	}
	return 0;
}
