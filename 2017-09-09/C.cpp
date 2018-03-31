#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define ll long long
#define M 1000000007
#define all(a) a.begin(), a.end()

int T, n, b;
int c[100100];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &b);
		for(int i = 1; i <= n; ++i) scanf("%d", c + i);
		int now = 0;
		bool flag = 1;
		for(int i = 1, x; i < n; ++i){
			scanf("%d", &x);
			now += c[i] - x * b;
			if(now < 0) flag = 0;
			
		}
		printf("%s\n", flag ? "Yes" : "No");
	}
	return 0;
}
