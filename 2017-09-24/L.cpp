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

int n;
int s[200100];

int c[10010];

int ask(int x){
	int res = 0;
	for(; x; x -= x & -x)
		res = max(res, c[x]);
	return res;
}

void add(int x, int v){
	for(; x <= 10000; x += x & -x)
		c[x] = max(c[x], v);
}

int main(){
	int x;
	while(~scanf("%d", &x)){
		if(x < 0) continue;
		s[++n] = x;
	}
	int ans = 0;
	for(int i = 1, f; i <= n; ++i){
		if(s[i] < 10000){
			f = ask(s[i]) + 1;
		}else{
			f = ask(s[i] - 10000) + 5;
		}
		add(s[i] + 1, f);
		ans = max(ans, f);
	}
	printf("%d\n", ans);
	
#ifndef ONLINE_JUDGE
	system("pause");
#endif
	return 0;
}
