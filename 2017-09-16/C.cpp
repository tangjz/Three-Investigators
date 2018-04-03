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
char s[20];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%s", s);
		int l = strlen(s);
		putchar('1');
		for(int i = 2; i <= 233; ++i){
			for(int j = 1; j < l; ++j)
				putchar('0');
			putchar('1');
		}
		puts("");
	}
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
