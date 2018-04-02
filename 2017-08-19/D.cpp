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
char s1[1000100], s2[1000100];
int p[1000100], f[1000100];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%s", s1 + 1);
		int n = strlen(s1 + 1);
		reverse(s1 + 1, s1 + n + 1);
		scanf("%s", s2 + 1);
		int m = strlen(s2 + 1);
		reverse(s2 + 1, s2 + m + 1);
		
		int j = 0; p[1] = 0; f[1] = 1;
		for(int i = 2; i <= m; ++i){
			while(j && s2[j + 1] != s2[i]) j = p[j];
			if(s2[j + 1] == s2[i]) ++j;
			p[i] = j;
			f[i] = (i + f[j]) % M;
		}
		j = 0;
		int res = 0;
		for(int i = 1; i <= n; ++i){
			while(j && s2[j + 1] != s1[i]) j = p[j];
			if(s2[j + 1] == s1[i]) ++j;
			res = (res + f[j]) % M;
			if(j == m){
				j = p[j];
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
