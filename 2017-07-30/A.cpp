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
int n, m;
char s[1010 * 1010];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		scanf("%s", s);
		for(int i = 0; i < n; puts(""), ++i)
			for(int j = 0; j < m; ++j){
				putchar(s[i * m + j]);
			}
	}
	
	return 0;
}
