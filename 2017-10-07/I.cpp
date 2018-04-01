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

char s[55];

int main(){
	scanf("%s", s);
	int n = strlen(s);
	
	ll x = 0, y = 0;
	for(int i = 0; i < n; ++i){
		int v = s[i] - '0';
		if(v & 1) x += 1 << (n - i - 1);
		if(v & 2) y += 1 << (n - i - 1);
	}
	
	printf("%d %lld %lld\n", n, x, y);
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
